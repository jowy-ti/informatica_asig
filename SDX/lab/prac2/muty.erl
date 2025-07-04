-module(muty).
-export([start/3, stop/0]).

% We use the name of the module (i.e. lock3) as a parameter to the start procedure. We also provide the average time (in milliseconds) the worker is going to sleep before trying to get the lock (Sleep) and work with the lock taken (Work).
% Transpas 39,40
start(Lock, Sleep, Work) ->
    Main = self(),
    spawn('worker1@127.0.0.1', fun()->register(w1, worker:start("John", Main, Lock, 1, Sleep, Work)) end),
    spawn('worker2@127.0.0.1', fun()->register(w2, worker:start("Ringo", Main, Lock, 2, Sleep, Work)) end),    
    spawn('worker3@127.0.0.1', fun()->register(w3, worker:start("Paul", Main, Lock, 3, Sleep, Work)) end),
    spawn('worker4@127.0.0.1', fun()->register(w4, worker:start("George", Main, Lock, 4, Sleep, Work)) end),
    collect(4, []).

% envía a los locks el listado de todos los locks que hay, también llamados nodos
collect(N, Locks) ->
    if
        N == 0 ->
            lists:foreach(fun(L) -> 
                L ! {peers, lists:delete(L, Locks)} 
            end, Locks);
        true ->
            receive
                {ready, L} ->
                    collect(N-1, [L|Locks])
            end
    end.

% función para enviar stop a los workers y después los workers enviar stop al gui y los locks
stop() ->
    {w1,'worker1@127.0.0.1'} ! stop,
    {w2,'worker2@127.0.0.1'} ! stop,
    {w3,'worker3@127.0.0.1'} ! stop,
    {w4,'worker4@127.0.0.1'} ! stop.

% erl -name worker1@127.0.0.1 -setcookie secret
% erl -name muty@127.0.0.1 -setcookie secret