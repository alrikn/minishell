/*
** EPITECH PROJECT, 2025
** bsminishell1
** File description:
** main
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "my.h"
#include "struct.h"

void env_parser(char **env, core_t *core)
{
    core->head = NULL;
    core->head = parse_env(env);
}

int main(int argc, char **argv, char **env)
{
    core_t core = {0};

    env_parser(env, &core);
    main_loop(&core);
    if (core.com.exit)
        my_cooler_putstr("exit\n");
    if (core.exit.rushed_exit) {
        return core.exit.last_failed ? 1 : core.exit.last_value;
    }
    return 0;
}
