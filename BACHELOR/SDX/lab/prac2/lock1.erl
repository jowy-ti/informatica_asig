-module(lock1).
-export([start/1]).

start(MyId) ->
    spawn(fun() -> init(MyId) end).

init(_) ->
    receive
        {peers, Nodes} ->
            open(Nodes);
        stop ->
            ok
    end.

% Proceso para "abrir" el lock. Permitir que los workers accedan a la sección crítica
open(Nodes) ->
    receive
        % Master = worker. Un worker esta pidiendo el lock para el
        {take, Master, Ref} ->
            Refs = requests(Nodes),
            wait(Nodes, Master, Refs, [], Ref);
        % Un lock pide permiso
        {request, From,  Ref} ->
            From ! {ok, Ref},
            open(Nodes);
        stop ->
            ok;
        {ok, _} ->
            %% delayed ok message
            open(Nodes);
        Error ->
            io:format("open: unsupported message: ~w~n", [Error]),
            open(Nodes)
    end.

% Pide permiso para poder acceder a la sección crítica a todos los Nodos, y devuelve Refs
requests(Nodes) ->
    lists:map(
      fun(P) -> 
        R = make_ref(), 
        P ! {request, self(), R}, 
        R 
      end, 
      Nodes).

% Todos los Nodos han dado permiso para acceder a la sección crítica
wait(Nodes, Master, [], Waiting, TakeRef) ->
    % Avisa al worker que se le ha dado el lock
    Master ! {taken, TakeRef},
    held(Nodes, Waiting);
wait(Nodes, Master, Refs, Waiting, TakeRef) ->
    receive
        % si un nodo pide permiso, se le añade a la lista de espera
        {request, From, Ref} ->
            wait(Nodes, Master, Refs, [{From, Ref}|Waiting], TakeRef);
        % Un nodo ha dado permiso
        {ok, Ref} ->
            NewRefs = lists:delete(Ref, Refs),
            wait(Nodes, Master, NewRefs, Waiting, TakeRef);
        % El worker ha acabado de trabajar
        release ->
            ok(Waiting),
            % Vuelve al estado abierto para dar el lock            
            open(Nodes);
	Error ->
            io:format("wait: unsupported message: ~w~n", [Error]),
            wait(Nodes, Master, Refs, Waiting, TakeRef)
    end.

% Notificar a los demas nodos que estaban en waiting que ya pueden intentar adquirir el lock
ok(Waiting) ->
    lists:foreach(
      fun({F,R}) -> 
        F ! {ok, R} 
      end, 
      Waiting).

held(Nodes, Waiting) ->
    receive
        % Otro worker pide el lock mientras el worker actual lo tiene en uso
        {request, From, Ref} ->
            % Lo añade a la lista de espera y vuelve a held
            held(Nodes, [{From, Ref}|Waiting]);
        % Enviado por el worker para indicar que ya ha acabado de trabajar
        release ->
            ok(Waiting),
            open(Nodes);
    {ok, _} ->
            %% delayed ok message
            held(Nodes, Waiting);
	Error ->
            io:format("held: unsupported message: ~w~n", [Error]),
            held(Nodes, Waiting)
    end.
