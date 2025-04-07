/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** leaf_handler
*/

#include "my.h"
#include "struct.h"
#include <string.h>

/*
 **this does both built ins and execve stuff
*/
int leaf_handler(core_t *core, char **argv, int input, int output)
{
    int return_value = 0;
    int argc = argc_counter(argv);

    if (!argv || argc == 0)
        return -84;
    check_system_commands(core, argv);
    if (argc >= 1 && my_strcmp(argv[0], "exit") == 0) {
        return 0;
    }
    if (core->com.flag == false) {
        core->sub_input.argv = argv;
        core->sub_input.env = list_to_array(core->head);
        return_value = leaf_executor(core, input, output);
        reset_sub_input(core);
    }
    return return_value;
}
