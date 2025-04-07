/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** echo_handler
*/

#include "my.h"
#include "struct.h"

int last_return_value(core_t *core)
{
    if (core->exit.last_failed) {
        my_put_nbr(1);
    } else
        my_put_nbr(core->exit.last_value);
    my_cooler_putstr("\n");
    return 0;
}

int write_normal_echo(core_t *core, char **argv)
{
    int i = 0;

    while (argv[i + 1]) {
        my_cooler_putstr(argv[i + 1]);
        i++;
        if (argv[i + 1]) {
            my_cooler_putstr(" ");
        }
    }
    my_cooler_putstr("\n");
    return 0;
}

int echo_handler(core_t *core, char **argv)
{
    int argc = argc_counter(argv);

    if (argc == 2 && my_strcmp(argv[1], "$?") == 0)
        return last_return_value(core);
    return write_normal_echo(core, argv);
}
