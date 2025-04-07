/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** free_array
*/

#include <stdlib.h>

int free_array(char **array)
{
    if (!array)
        return 1;
    for (int i = 0; array[i] != NULL; i++) {
        free(array[i]);
        array[i] = NULL;
    }
    free(array);
    array = NULL;
    return 0;
}
