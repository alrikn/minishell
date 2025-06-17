/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** alias_expansion
*/

#include "my.h"

argv_t *get_alias_expansion(core_t *core, char *command)
{
    char *alias_command = NULL;

    if (!command) {
        return NULL;
    }
    alias_command = find_alias(core->alias_head, command);
    if (!alias_command) {
        return NULL;
    }
    return input_line_parser(alias_command);
}

int exec_alias(core_t *core, argv_t *alias_expansion, int input, int output)
{
    int return_value = 0;

    check_system_commands(core, alias_expansion, input, output);
    if (core->com.flag == false) {
        core->sub_input.argv = alias_expansion->argv;
        core->sub_input.env = list_to_array(core->head);
        return_value = leaf_executor(core, input, output);
        reset_sub_input(core);
    }
    free_argv_t(alias_expansion);
    return return_value;
}
