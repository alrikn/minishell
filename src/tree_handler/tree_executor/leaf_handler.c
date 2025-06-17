/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** leaf_handler
*/

#include "my.h"
#include "struct.h"

/*
 **this does both built ins and execve stuff
 **it chooses whether we are executing builtin or real command
*/
int leaf_handler(core_t *core, argv_t *argv_struct, int input, int output)
{
    int return_value = 0;
    int argc = argc_counter(argv_struct->argv);
    argv_t *alias_expansion = NULL;

    if (!argv_struct->argv || argc == 0)
        return -84;
    alias_expansion = get_alias_expansion(core, argv_struct->argv[0]);
    if (alias_expansion)
        return exec_alias(core, alias_expansion, input, output);
    check_system_commands(core, argv_struct, input, output);
    if (argc >= 1 && my_strcmp(argv_struct->argv[0], "exit") == 0)
        return 0;
    if (core->com.flag == false) {
        core->sub_input.argv = argv_struct->argv;
        core->sub_input.env = list_to_array(core->head);
        return_value = leaf_executor(core, input, output);
        reset_sub_input(core);
    }
    return return_value;
}
