/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** print_array
*/

#include <unistd.h>

#include "my.h"

int print_array(char **array)
{
    int argc = argc_counter(array);

    for (int i = 0; i < argc; i++) {
        my_cooler_putstr(array[i]);
        if (i != argc -1)
            my_cooler_putstr(" ");
    }
    return argc;
}
