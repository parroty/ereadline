ereadline
=====
A readline wrapper for Erlang.

It has very limited functionality at the moment with the following functions.
- readline
- add_history

It requires `rebar` and `readline` library to compile and work.

## Sample

```erlang
-module(ereadline_demo).
-compile(export_all).

go() ->
    ereadline:add_history("history1"),
    ereadline:add_history("history2"),
    read_inputs().

read_inputs() ->
    String = ereadline:readline("user> "),
    case String of
      {error, _} -> ok;
      "exit" -> ok;
      "quit" -> ok;
      Line ->
          io:format("returned input = ~s~n", [Line]),
          ereadline:add_history(Line),
          read_inputs()
    end.
```

## Usage

```sh
> git clone https://github.com/parroty/ereadline
> cd ereadline
> make
> ./run.escript
```

## Notes
- Use `ctrl+D` key for getting out of `ereadline:readline`. Then the function returns with `{error, "empty"}`.
