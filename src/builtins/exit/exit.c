/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** exit
*/

#include "my.h"
#include "struct.h"

static void exit_error(void)
{
    my_cooler_putstr("exit: Expression Syntax.\n");
}

/*
**assume argc == 2
*/
static int exit_parser(core_t *core, char **argv)
{
    if (my_is_num(argv[1])) {
        core->com.exit = true;
        core->com.flag = true;
        core->com.exit_value = my_str_to_int(argv[1]);
        return 0;
    } else {
        exit_error();
        return 84;
    }
}

/*
** basically since the user can input "exit 12"
and expect the return value to be 12 we need to keep and return 12
*/
int exit_builtin(core_t *core, argv_t *argv_struct, int input, int output)
{
    int argc = argc_counter(argv_struct->argv);

    if (argc > 2) {
        exit_error();
        return 84;
    }
    if (my_strcmp("exit", argv_struct->argv[0]) == 0) {
        if (argc == 2) {
            return exit_parser(core, argv_struct->argv);
        } else {
            core->com.exit = true;
            core->com.flag = true;
        }
    }
    return 0;
}
