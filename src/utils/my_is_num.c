/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** my_is_num
*/

#include <stdbool.h>

static bool is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

/*
**if the str is a num then we return true if it iesnt then its false
*/
bool my_is_num(const char *str)
{
    int i = 0;

    while (str[i]) {
        if (!is_digit(str[i]))
            return false;
        i++;
    }
    return true;
}
