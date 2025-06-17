/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** builtin_handler
*/

#include "my.h"
#include "struct.h"
#include <stdbool.h>
#include <signal.h>

/*
 ** Here we have all the builtins stored with their corresponding functions
 ** implemented in a way where if we want a new builtin, we just have to
 ** add a new element to the enum in struct.h and add a new element inside
 ** this array. This way, we can add as many builtins as we want without
 ** having to worry abt coding style.
*/
const builtin_tuple_t builtin_map[BUILTIN_MAX] = {
    [BN_ENV] = {
        .bn_name = "env",
        .bn_function = print_env,
    },
    [BN_CD] = {
        .bn_name = "cd",
        .bn_function = cd_handler,
    },
    [BN_SETENV] = {
        .bn_name = "setenv",
        .bn_function = setenv_direct,
    },
    [BN_UNSETENV] = {
        .bn_name = "unsetenv",
        .bn_function = unsetenv_direct,
    },
    [BN_ECHO] = {
        .bn_name = "echo",
        .bn_function = echo_handler,
    },
    [BN_EXIT] = {
        .bn_name = "exit",
        .bn_function = exit_builtin,
    },
    [BN_FG] = {
        .bn_name = "fg",
        .bn_function = fg_handler,
    },
    [BN_BG] = {
        .bn_name = "fg",
        .bn_function = fg_handler
    },
    [BN_JOBS] = {
        .bn_name = "jobs",
        .bn_function = jobs_handler,
    },
    [BN_ALIAS] = {
        .bn_name = "alias",
        .bn_function = alias_handler,
    },
    [BN_UNALIAS] = {
        .bn_name = "unalias",
        .bn_function = unalias_handler,
    },
    [BN_HISTORY] = {
        .bn_name = "history",
        .bn_function = history_print,
    },
};

/*
 ** this resetss the flags to ensure that loops do'nt interfere with each other
 ** the flag boolean is set to true if we are calling one of the builtins
 ** last_failed if the builtin that we called in the loop failed
 */
void flag_reset(core_t *core)
{
    core->com.flag = false;
    core->exit.last_failed = false;
}

/*
** just a func array I DO NOT CHECK THE AMOUNT OF ARGUMENTS HERE
** error handling has to be done intra builtin
*/
static int flag_catch(
    core_t *core, argv_t *argv_struct, int input_fd, int output_fd)
{
    for (int i = 0; i < BUILTIN_MAX; i++)
        if (argv_struct->argv && argv_struct->argv[0] &&
            !strcmp(builtin_map[i].bn_name, argv_struct->argv[0])) {
            core->com.flag = true;
            return builtin_map[i].bn_function(core, argv_struct, input_fd,
                output_fd);
        }
    return 0;
}

/*
 ** this checks the flags(cd, env, setenv, unsetenv, exit)
 ** exit is checked separately, because it is the only builtin
 that is not linked
 to an actual function
*/
int check_system_commands(core_t *core, argv_t *argv_struct, int in, int out)
{
    int len = my_strlen(argv_struct->argv[0]);

    flag_reset(core);
    if (len == 0)
        return 1;
    if (flag_catch(core, argv_struct, in, out) != 0) {
        core->exit.last_failed = true;
    }
    return 0;
}
