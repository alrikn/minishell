/*
** EPITECH PROJECT, 2025
** bsminishell1
** File description:
** main
*/

#include <bits/posix1_lim.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "struct.h"
#include <ncurses.h>

void handle_interrupt(int signal)
{
    if (signal == SIGINT) {
        printf("\n$> ");
        fflush(STDIN_FILENO);
    }
}

void ignore_signals(core_t *core)
{
    signal(SIGINT, handle_interrupt);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
}

void env_parser(char **env, core_t *core)
{
    core->head = NULL;
    core->head = parse_env(env);
    if (!core->head) {
        no_environment(core);
    } else {
        update_shlvl(core);
    }
}

int main(int argc, char **argv, char **env)
{
    core_t core = {0};

    env_parser(env, &core);
    ignore_signals(&core);
    core.alias_head = NULL;
    if (isatty(STDIN_FILENO))
        history_parse(&core);
    main_loop(&core);
    if (core.com.exit)
        my_cooler_putstr("exit\n");
    if (core.exit.rushed_exit) {
        return core.exit.last_failed ? 1 : core.exit.last_value;
    }
    return core.com.exit_value;
}
