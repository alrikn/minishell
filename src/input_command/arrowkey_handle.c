/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** arrowkey_handle.c
*/

#include <stdbool.h>
#include <string.h>

int right_arrow(int *char_index, bool *escape_sequence, char *input)
{
    *escape_sequence = false;
    if (*char_index < (strlen(input))) {
        (*char_index)++;
        return 1;
    }
    return 0;
}

int left_arrow(int *char_index, bool *escape_sequence)
{
    *escape_sequence = false;
    if (*char_index > 0) {
        (*char_index)--;
        return -1;
    }
    return 0;
}

int up_arrow(int *char_index, bool *escape_sequence)
{
    *escape_sequence = false;
    return 0;
}

int down_arrow(int *char_index, bool *escape_sequence)
{
    *escape_sequence = false;
    return 0;
}
