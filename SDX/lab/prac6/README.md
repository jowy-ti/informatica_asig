# LAB6: Chordy

## Compilar los códigos

```erl
c(chordy).
c(key).
c(storage).
c(node1).
```


## MS1

```
N2 = node1:start(2).
N4 = node1:start(4,N2).
N0 = node1:start(0,N2).
N3 = node1:start(3,N2).
N1 = node1:start(1,N2).
N0 ! probe.
```
## MS2

```
erl -name node1@127.0.0.1 
register(node1, node1:start(4))

```

```
N1 = node1:start(1, {node1, 'node1@127.0.0.1'})
```


```
P = chordy:connect(N2).
P ! {add,1,1}.
N1 ! stop.
```

## MS3

- Nodo N1
erl -name N1@127.0.0.1 
register(n1, node2:start(1)).
P = chordy:connect(n1).
P ! {add, 2, 2}.
P ! {add, 1, 1}.
P ! {add, 30, 30}.
n1 ! probe.

- Nodo N0
erl -name N0@127.0.0.1 
N0 = node2:start(0, {n1, 'N1@127.0.0.1'}).
N0 ! probe.

- Nodo N2
erl -name N2@127.0.0.1 
N2 = node2:start(2, {n1, 'N1@127.0.0.1'}).
N2 ! probe.

- Nodo N1
P ! {lookup,2}.

## MS4

- Nodo N1
erl -name N1@127.0.0.1 
register(n1, node3:start(1)).

- Nodo N0
erl -name N0@127.0.0.1 
N0 = node3:start(0, {n1, 'N1@127.0.0.1'}).

- Nodo N2
erl -name N2@127.0.0.1 
N2 = node3:start(2, {n1, 'N1@127.0.0.1'}).


n1 ! probe.
N0 ! stop.
n1 ! probe.
N2 ! stop.
n1 ! probe.

## MS5

- Nodo N1
erl -name N1@127.0.0.1 
register(n1, node4:start(1)).
P = chordy:connect(n1).
P ! {add,30,30}.
P ! {add,1,1}.
P ! {add,2,2}.

- Nodo N0
erl -name N0@127.0.0.1 
N0 = node4:start(0, {n1, 'N1@127.0.0.1'}).

- Nodo N2
erl -name N2@127.0.0.1 
N2 = node4:start(2, {n1, 'N1@127.0.0.1'}).


n1 ! probe.
N0 ! stop.
n1 ! probe.
N2 ! stop.
n1 ! probe.