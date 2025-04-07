/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** first_char
*/

#include <stdio.h>

char *first_char(const char *str, const char c)
{
    if (!str)
        return NULL;
    while (*str) {
        if (*str == c) {
            return (char *)str;
        }
        str++;
    }
    if (c == '\0')
        return (char *)str;
    return NULL;
}
