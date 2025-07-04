-module(lock2).
-export([start/1]).

start(MyId) ->
    spawn(fun() -> init(MyId) end).

% Nodes: son los PIDS de los locks que están activos
init(MyId) ->
    receive
        {peers, Nodes} ->
            open(Nodes, MyId);
        stop ->
            ok
    end.

% Estado del worker open, no está en región crítica ni espera para estarlo

open(Nodes, MyId) ->
    receive
        % Enviado por el worker para pedir el lock
        {take, Master, Ref} ->
            Refs = requests(Nodes, MyId),
            wait(Nodes, Master, Refs, [], Ref, MyId);
        % No nos importa el valor "_" (comodín)
        {request, From,  Ref, _} ->
            From ! {ok, Ref},
            open(Nodes, MyId);
        stop ->
            ok;
        {ok, _} ->
            %% delayed ok message
            open(Nodes, MyId);
        Error ->
            io:format("open: unsupported message: ~w~n", [Error]),
            open(Nodes, MyId)
    end.

% Pide permiso para poder acceder a la sección crítica a todos los Nodos, y devuelve Refs
requests(Nodes, MyId) ->
    lists:map(
      fun(P) -> 
        R = make_ref(), 
        P ! {request, self(), R, MyId}, 
        R 
      end, 
      Nodes).

% TakeRef: Ref de la request del worker asociado al lock para entrar en la región crítica
% Refs: lista de Ref de las requests de los workers que te tienen que dar el ok
% Waiting: lista de Ref de las requests de los workers que tienes que darles el ok
% Master: PID del worker asociado al lock
% Estado del worker wait, está esperando a recibir el ok de todos los workers asociados a los locks para entrar a la región crítica

wait(Nodes, Master, [], Waiting, TakeRef, MyId) ->
    Master ! {taken, TakeRef},
    held(Nodes, Waiting, MyId);

wait(Nodes, Master, Refs, Waiting, TakeRef, MyId) ->
    receive
        % ReqId <- prioridad del lock que pide permiso
        {request, From, Ref, ReqId} ->
            % Si el lock que pide permiso tiene más prioridad...
            if ReqId < MyId ->
                From ! {ok, Ref},
                R = make_ref(),
                % Vuelve a pedir permiso. El lock con más prioridad lo metera en la cola de espera
                From ! {request, self(), R, MyId},
                % Añade la referencia a la lista, ya que el lock con más prio le tendra que dar el ok para poder acceder a la región crítica
                wait(Nodes, Master, [R|Refs], Waiting, TakeRef, MyId); 
            true ->
                wait(Nodes, Master, Refs, [{From, Ref}|Waiting], TakeRef, MyId) % El ReqID tiene menos prio, se tiene que esperar
            end;
        {ok, Ref} ->
            NewRefs = lists:delete(Ref, Refs),
            wait(Nodes, Master, NewRefs, Waiting, TakeRef, MyId);
        release ->
            ok(Waiting),            
            open(Nodes, MyId);
	Error ->
            io:format("wait: unsupported message: ~w~n", [Error]),
            wait(Nodes, Master, Refs, Waiting, TakeRef, MyId)
    end.

ok(Waiting) ->
    lists:foreach(
      fun({F,R}) -> 
        F ! {ok, R} 
      end, 
      Waiting).

% Estado del worker en la región crítica, no dejará la región crítica hasta que acabe la faena

held(Nodes, Waiting, MyId) ->
    receive
        {request, From, Ref, _} ->
            held(Nodes, [{From, Ref}|Waiting], MyId);
        release ->
            ok(Waiting),
            open(Nodes, MyId);
    {ok, _} ->
            %% delayed ok message
            held(Nodes, Waiting, MyId);
	Error ->
            io:format("held: unsupported message: ~w~n", [Error]),
            held(Nodes, Waiting, MyId)
    end.
