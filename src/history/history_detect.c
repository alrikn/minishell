/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** history_detect
*/

#include "my.h"
#include "struct.h"


bool is_history_str(char *str)
{
    if (!str)
        return false;
    if (str[0] == '!')
        return true;
    return false;
}

/*
** this checks every word
** if there is at least one history command, it returns true
*/
bool contains_history_command(core_t *core, argv_t *argv_struct)
{
    if (!argv_struct || !argv_struct->argv || !argv_struct->types)
        return false;
    for (int i = 0; argv_struct->argv[i]; i++) {
        if (argv_struct->argv[i][0] == '!')
            return true;
    }
    return false;
}
