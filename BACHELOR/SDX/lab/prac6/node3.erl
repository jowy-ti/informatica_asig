-module(node3).
-export([start/1, start/2]).

-define(Stabilize, 1000).
-define(Timeout, 5000).

start(MyKey) ->
    start(MyKey, nil).

start(MyKey, PeerPid) ->
    timer:start(),
    spawn(fun() -> init(MyKey, PeerPid) end).

init(MyKey, PeerPid) ->
    Predecessor = nil,
    {ok, Successor} = connect(MyKey, PeerPid),
    schedule_stabilize(),
    Next = nil,     %% Next es el siguiente nodo en la cadena de sucesores, inicialmente no hay ninguno
    Store = storage:create(),
    node(MyKey, Predecessor, Successor, Next, Store).

connect(MyKey, nil) ->
    {ok, {MyKey , nil, self()}};    %% TODO: OK -> no hay más nodos, somos nuestro propio sucesor
connect(_, PeerPid) ->
    Qref = make_ref(),
    PeerPid ! {key, Qref, self()},
    receive
        {Qref, Skey} ->     %% recibimos el Key del sucesor
            {ok, {Skey, monit(PeerPid), PeerPid}}    %% TODO: OK -> monit(PeerPid) para vigilar al sucesor
    after ?Timeout ->
        io:format("Timeout: no response from ~w~n", [PeerPid])
    end.

schedule_stabilize() ->
    timer:send_interval(?Stabilize, self(), stabilize).

node(MyKey, Predecessor, Successor, Next, Store) ->
    receive 
        {key, Qref, Peer} ->
            Peer ! {Qref, MyKey},
            node(MyKey, Predecessor, Successor, Next, Store);
        {notify, NewPeer} ->
            {NewPredecessor, NewStore} = notify(NewPeer, MyKey, Predecessor, Store),
            node(MyKey, NewPredecessor, Successor, Next, NewStore); %% "creamos" un NUEVO nodo con los datos de su predecesor y los nuevos valores de su Storage
        {request, Peer} ->
            request(Peer, Predecessor, Successor),
            node(MyKey, Predecessor, Successor, Next, Store);
        {status, Pred, Nx} ->
            {NewSuccessor, NewNext} = stabilize(Pred, Nx, MyKey, Successor),
            node(MyKey, Predecessor, NewSuccessor, NewNext, Store);
        stabilize ->
            stabilize(Successor),
            node(MyKey, Predecessor, Successor, Next, Store);
        {add, Key, Value, Qref, Client} ->
            Added = add(Key, Value, Qref, Client, MyKey, Predecessor, Successor, Store),
            node(MyKey, Predecessor, Successor, Next, Added);
        {lookup, Key, Qref, Client} ->
            lookup(Key, Qref, Client, MyKey, Predecessor, Successor, Store),
            node(MyKey, Predecessor, Successor, Next, Store);
        {handover, Elements} ->
            NewStore = storage:merge(Store, Elements),  %% merge de los datos de nuestro Store con los datos que nos pasan
            node(MyKey, Predecessor, Successor, Next, NewStore);
        {'DOWN', Ref, process, _, _} ->
            {NewPred, NewSucc, NewNext} = down(Ref, Predecessor, Successor, Next),
            node(MyKey, NewPred, NewSucc, NewNext, Store);
        stop ->
            ok;
        probe ->
            create_probe(MyKey, Successor, Store),
            node(MyKey, Predecessor, Successor, Next, Store);
        {probe, MyKey, Nodes, T} ->
            remove_probe(MyKey, Nodes, T),
            node(MyKey, Predecessor, Successor, Next, Store);
        {probe, RefKey, Nodes, T} ->
            forward_probe(MyKey, RefKey, [MyKey|Nodes], T, Successor, Store),
            node(MyKey, Predecessor, Successor, Next, Store);
        Error ->
            io:format("Reception of strange message ~w~n", [Error]),
            node(MyKey, Predecessor, Successor, Next, Store)
   end.

stabilize(Pred, Next, MyKey, Successor) ->
  {Skey, Sref, Spid} = Successor,
  case Pred of
      nil ->    %% nuestro nodo sucesor no tiene predecesor, en todo caso somos nosotros su predecesor
          Spid ! {notify, {MyKey, self()}},     %% TODO: OK -> notificamos al sucesor de nuestro id
          {Successor, Next};
      {MyKey, _} ->     %% somos el predecesor de nuestro sucesor -> todo OK
          {Successor, Next};
      {Skey, _} ->      %% el predecesor de nuestro sucesor es el mismo
          Spid ! {notify, {MyKey, self()}},     %% TODO: OK -> Como es nuestro sucesor, le decimos que somos su predecesor
          {Successor, Next};
      {Xkey, Xpid} ->
            %% mira si Xkey esta entre MyKey y Skey
            case key:between(Xkey, MyKey, Skey) of
                true ->     %% MKey --- Xkey --- Skey
                    demonit(Sref),  %% dejamos de vigilar al sucesor antiguo
                    self() ! stabilize, %%
                    {{Xkey, monit(Xpid), Xpid}, {Skey, Spid}}; %% Ahora sabemos que X es nuestro sucesor, y que S es es sucesro de X
                false ->
                    Spid ! {notify, {MyKey, self()}}, %% TODO: OK -> como Xkey no esta entre MyKey y Skey, le decimos a nuestro sucesor que somos su predecesor
                    {Successor, Next} %%
            end
    end.

%% ignoramos Skey y Sref, solo nos interesa el ID del sucesor
stabilize({_, _, Spid}) ->
    Spid ! {request, self()}.

%% El nodo Peer es el nodo que nos ha pedido el status de nuestro predecesor y sucesor
request(Peer, Predecessor, {Skey, _, Spid}) ->
    case Predecessor of
        nil ->
            Peer ! {status, nil, {Skey, Spid}};
        {Pkey, _, Ppid} ->
            Peer ! {status, {Pkey, Ppid}, {Skey, Spid}}
    end.

%% Devuelve el predecesor y su store
notify({Nkey, Npid}, MyKey, Predecessor, Store) ->
    case Predecessor of
        nil ->
            Keep = handover(Store, MyKey, Nkey, Npid),
            {{Nkey, monit(Npid), Npid}, Keep};   %% las Keys del nuevo nodo ya se las enviamos a el con la función handover
        {Pkey, Pref, _} ->
            case key:between(Nkey, Pkey, MyKey) of
                true ->     %% Nkey esta entre Pkey y MyKey, el nudvo nodo es nuestro predecesor
                  Keep = handover(Store, MyKey, Nkey, Npid), %%
                  demonit(Pref),    %% dejamos de vigilar al predecesor antiguo
                  {{Nkey, monit(Npid), Npid}, Keep};  
                false ->
                  {Predecessor, Store}
            end
    end.

%% client = PID
%% Store -> lista donde se almacenan los datos
add(Key, Value, Qref, Client, _, nil, {_, _, Spid}, Store) ->  %% no somos responsables de la Key
  Spid ! {add, Key, Value, Qref, Client},
  Store;

add(Key, Value, Qref, Client, MyKey, {Pkey, _, _}, {_, _, Spid}, Store) ->
  case key:between(Key, Pkey, MyKey) of %% si la Key esta entre Pkey y MyKey, entonces la tenemos que gaurdar nosotros
    true ->
      Added = storage:add(Key, Value, Store),
      Client ! {Qref, ok},
      Added;
    false ->
      Spid ! {add, Key, Value, Qref, Client},
      Store
  end.

lookup(Key, Qref, Client, _, nil, {_, _, Spid}, _) ->  %% no somos responsables de la Key -> forward
  Spid ! {lookup, Key, Qref, Client};

lookup(Key, Qref, Client, MyKey, {Pkey, _, _}, {_, _, Spid}, Store) ->
  case key:between(Key, Pkey, MyKey) of
    true ->   %% tenemos que buscar la Key en nuestro Store
      Result = storage:lookup(Key, Store),
      Client ! {Qref, Result};
    false ->
      Spid ! {lookup, Key, Qref, Client}
  end.

%% Separar el Store en dos, uno para nosotros y otro para el nuevo nodo en funcion de la Keys
handover(Store, MyKey, Nkey, Npid) ->
    {Keep, Leave} = storage:split(MyKey, Nkey, Store),
    Npid ! {handover, Leave},  %% enviamos los datos que no nos corresponden al nuevo nodo
    Keep. 

monit(Pid) ->
    erlang:monitor(process, Pid).

demonit(nil) ->
    ok;
demonit(MonitorRef) ->
    erlang:demonitor(MonitorRef, [flush]).

%% {NewPred, NewSucc, NewNext}
down(Ref, {_, Ref, _}, Successor, Next) -> %% si el predecesor ha muerto...
    {nil, Successor, Next}; 
down(Ref, Predecessor, {_, Ref, _}, {Nkey, Npid}) -> %% si el sucesor ha muerto...
    self() ! stabilize,     %% estabilizar porque lo pone en el doc
    {Predecessor, {Nkey, monit(Npid), Npid}, nil}. %% Actualimos nuestro nuevo succesor


    
create_probe(MyKey, {_, _, Spid}, Store) ->
    Spid ! {probe, MyKey, [MyKey], erlang:monotonic_time()},
    io:format("Node ~w created probe -> Store: ~w~n", [MyKey, Store]).
	
remove_probe(MyKey, Nodes, T) ->
    T2 = erlang:monotonic_time(),
    Time = erlang:convert_time_unit(T2-T, native, microsecond),
    io:format("Node ~w received probe after ~w us -> Ring: ~w~n", [MyKey, Time, Nodes]).
	
forward_probe(MyKey, RefKey, Nodes, T, {_, _, Spid}, Store) ->
    Spid ! {probe, RefKey, Nodes, T},
    io:format("Node ~w forwarded probe started by node ~w -> Store: ~w~n", [MyKey, RefKey, Store]).
  