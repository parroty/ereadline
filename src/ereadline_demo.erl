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
          read_inputs()
    end.
