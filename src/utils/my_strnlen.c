/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** my_strnlen
*/

int my_strnlen(const char *src, int num)
{
    int len = 0;

    while (len < num && src[len] != '\0') {
        len++;
    }
    return len;
}
