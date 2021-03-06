#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "erl_nif.h"
#include "ereadline.h"

static ErlNifMutex* g_lock = NULL;

/* nif functions */
static int
load(ErlNifEnv* env, void** priv, ERL_NIF_TERM load_info) {
    g_lock = enif_mutex_create("g_lock");
    return 0;
}

static void
unload(ErlNifEnv* env, void* priv) {
    if(g_lock != NULL) {
        enif_mutex_destroy(g_lock);
    }
}


/* helper functions */
static ERL_NIF_TERM
result_code(ErlNifEnv* env, int code) {
    if(code == 0) {
        return enif_make_atom(env, "ok");
    } else {
        return enif_make_tuple2(
                   env,
                   enif_make_atom(env, "error"),
                   enif_make_int(env, code)
               );
    }
}

static ERL_NIF_TERM
result_string(ErlNifEnv* env, char *string) {
    if(string != NULL) {
        return enif_make_string(env, string, ERL_NIF_LATIN1);
    } else {
        return enif_make_tuple2(
                   env,
                   enif_make_atom(env, "error"),
                   enif_make_string(env, "empty", ERL_NIF_LATIN1)
               );
    }
}

/* api functions */
static ERL_NIF_TERM
e_readline(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    int length;
    enif_get_int(env, argv[0], &length);
    char buf[length + 1];
    if(enif_get_string(env, argv[1], buf, length + 1, ERL_NIF_LATIN1) < 1) {
        return enif_make_badarg(env);
    }

    enif_mutex_lock(g_lock);
    char *string;
    string = readline(buf);
    enif_mutex_unlock(g_lock);

    ERL_NIF_TERM result = result_string(env, string);
    free(string);
    return result;
}

// add_history
static ERL_NIF_TERM
e_add_history(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    int length;
    enif_get_int(env, argv[0], &length);
    char buf[length + 1];
    if(enif_get_string(env, argv[1], buf, length + 1, ERL_NIF_LATIN1) < 1) {
        return enif_make_badarg(env);
    }

    enif_mutex_lock(g_lock);
    int code = add_history(buf);
    enif_mutex_unlock(g_lock);

    return result_code(env, code);
}


static ErlNifFunc nif_funcs[] = {
    {"e_readline", 2, e_readline},
    {"e_add_history", 2, e_add_history},
};

ERL_NIF_INIT(ereadline, nif_funcs, load, NULL, NULL, unload)
