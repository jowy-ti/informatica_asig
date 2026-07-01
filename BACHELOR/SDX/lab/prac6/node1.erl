-module(node1).
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
    node(MyKey, Predecessor, Successor).

%% nil -> es el primer nodo del anillo
connect(MyKey, nil) ->
    {ok, {MyKey , self()}};    %% TODO: OK -> no hay más nodos, somos nuestro propio sucesor
connect(_, PeerPid) ->
    Qref = make_ref(),
    PeerPid ! {key, Qref, self()},
    receive
        {Qref, Skey} ->     %% recibimos el Key del sucesor
            {ok, {Skey , PeerPid}}    %% TODO: OK
    after ?Timeout ->
        io:format("Timeout: no response from ~w~n", [PeerPid])
    end.

schedule_stabilize() ->
    timer:send_interval(?Stabilize, self(), stabilize).

% Myke -> id único del nodo
% nil = null, para indicar que no hay predecesor o sucesor
node(MyKey, Predecessor, Successor) ->
    receive 
        {key, Qref, Peer} ->
            Peer ! {Qref, MyKey},
            node(MyKey, Predecessor, Successor);
        {notify, NewPeer} ->
            NewPredecessor = notify(NewPeer, MyKey, Predecessor),
            node(MyKey, NewPredecessor, Successor);
        {request, Peer} ->
            request(Peer, Predecessor),
            node(MyKey, Predecessor, Successor);
        {status, Pred} ->
            NewSuccessor = stabilize(Pred, MyKey, Successor),
            node(MyKey, Predecessor, NewSuccessor);
        stabilize ->
            stabilize(Successor),
            node(MyKey, Predecessor, Successor);
        stop ->
            ok;
        probe ->
            create_probe(MyKey, Successor),
            node(MyKey, Predecessor, Successor);
        {probe, MyKey, Nodes, T} ->
            remove_probe(MyKey, Nodes, T),
            node(MyKey, Predecessor, Successor);
        {probe, RefKey, Nodes, T} ->
            forward_probe(MyKey, RefKey, [MyKey|Nodes], T, Successor),
            node(MyKey, Predecessor, Successor);
        Error ->
            io:format("Reception of strange message ~w~n", [Error]),
            node(MyKey, Predecessor, Successor)
   end.

%% params: Predecesor del sucesor, id del nodo actual, sucesor del nodo actual
%% return: sucesor del nodo actual (MyKey, Spid)
stabilize(Pred, MyKey, Successor) ->
  {Skey, Spid} = Successor,
  case Pred of
      nil ->    %% nuestro nodo sucesor no tiene predecesor, en todo caso somos nosotros su predecesor
          Spid ! {notify, {MyKey, self()}},     %% TODO: OK -> notificamos al sucesor de nuestro id
          Successor;
      {MyKey, _} ->     %% somos el predecesor de nuestro sucesor -> todo OK
          Successor;
      {Skey, _} ->      %% el predecesor de nuestro sucesor es el mismo
          Spid ! {notify, {MyKey, self()}},     %% TODO: OK -> Como es nuestro sucesor, le decimos que somos su predecesor
          Successor;
      {Xkey, Xpid} ->
            %% mira si Xkey esta entre MyKey y Skey
            case key:between(Xkey, MyKey, Skey) of
                true ->     %% MKey --- Xkey --- Skey
                    self() ! stabilize, %% TODO: OK -> como Xkey esta entre MyKey y Skey, le decimos a nuestro nodo que se estabilice
                    Pred;   %% TODO: OK -> como Xkey esta entre MyKey y Skey, el es nuestro sucesor
                false ->
                    Spid ! {notify, {MyKey, self()}}, %% TODO: OK -> como Xkey no esta entre MyKey y Skey, le decimos a nuestro sucesor que somos su predecesor
                    Successor %% TODO: OK -> como Xkey no esta entre MyKey y Skey, continuamos con el mismo sucesor
            end
    end.

stabilize({_, Spid}) ->
    Spid ! {request, self()}.

request(Peer, Predecessor) ->
    case Predecessor of
        nil ->
            Peer ! {status, nil};
        {Pkey, Ppid} ->
            Peer ! {status, {Pkey, Ppid}}
    end.

%% Devuelve el predecesor
notify({Nkey, Npid}, MyKey, Predecessor) ->
    case Predecessor of
        nil ->      %% el predecesor es nil, por lo que no hay predecesor
           {Nkey, Npid}; %% TODO: OK -> como no hay predecesor, ponemos al nuevo nodo
        {Pkey,  _} ->
            case key:between(Nkey, Pkey, MyKey) of
                true ->
                    {Nkey, Npid};   %% TODO: OK -> Pkey --- Nkey --- MyKey -> Nkey es nuestro predecesor
                false -> 
                    Predecessor     %% TODO: Ok -> Nkey no esta entre Pkey y MyKey, por lo que seguimos con el mismo predecesor
            end
    end.

create_probe(MyKey, {_, Spid}) ->
    Spid ! {probe, MyKey, [MyKey], erlang:monotonic_time()},
    io:format("Node ~w created probe~n", [MyKey]).
	
remove_probe(MyKey, Nodes, T) ->
    T2 = erlang:monotonic_time(),
    Time = erlang:convert_time_unit(T2-T, native, microsecond),
    io:format("Node ~w received probe after ~w us -> Ring: ~w~n", [MyKey, Time, Nodes]).
	
forward_probe(MyKey, RefKey, Nodes, T, {_, Spid}) ->
    Spid ! {probe, RefKey, Nodes, T},
    io:format("Node ~w forwarded probe started by node ~w~n", [MyKey, RefKey]).
