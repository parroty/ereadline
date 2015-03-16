-module(ereadline).

-on_load(load_nif/0).

-export([
        readline/1,
        add_history/1
    ]).

%% =============================================================================
%% NIF Loading
%% =============================================================================

load_nif() ->
    Dir = case code:priv_dir(ereadline) of
        {error, bad_name} ->
            filename:dirname(code:which(?MODULE)) ++ "/../priv";
        OtherDir -> OtherDir
    end,
    erlang:load_nif(Dir ++ "/ereadline", 0).

%% =============================================================================
%% Application API
%% =============================================================================

readline(String) ->
    e_readline(erlang:iolist_size(String), String).

add_history(String) ->
    e_add_history(erlang:iolist_size(String), String).

%% =============================================================================
%% Internal functions
%% =============================================================================

e_readline(_StrLen, _Str) ->
    not_initialized.

e_add_history(_StrLen, _Str) ->
    not_initialized.
