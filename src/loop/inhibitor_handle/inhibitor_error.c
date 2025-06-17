/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** inhibitor_error
*/

#include "my.h"
#include "struct.h"

/*
** when this returns true,
stop everything cus smth went wrong with inhibitors
*/
bool inhibitor_error(argv_t *argv_struct)
{
    int i = 0;

    if (!argv_struct || !argv_struct->argv || !argv_struct->types)
        return true;
    while (argv_struct->argv[i] && argv_struct->types[i] != NONE) {
        if (argv_struct->types[i] == ERROR)
            return true;
        i++;
    }
    if (argv_struct->types[i] == ERROR)
            return true;
    return false;
}
