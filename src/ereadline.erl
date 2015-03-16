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

readline(String) when is_list(String) ->
    Str = lists:flatten(String),
    e_readline(erlang:iolist_size(Str), Str).

add_history(String) when is_list(String) ->
    Str = lists:flatten(String),
    e_add_history(erlang:iolist_size(Str), Str).

%% =============================================================================
%% Internal functions
%% =============================================================================

e_readline(_StrLen, _Str) ->
    not_initialized.

e_add_history(_StrLen, _Str) ->
    not_initialized.
