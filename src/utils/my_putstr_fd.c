/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** my_putstr_fd
*/

#include <unistd.h>

static int my_strlen(char const *str)
{
    int len = 0;

    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int my_putstr_fd(char const *str, int output_fd)
{
    int len;
    int written;

    if (!str) {
        write(1, "(null)", 6);
        return -1;
    }
    len = my_strlen(str);
    written = write(output_fd, str, len);
    if (written != len) {
        return -1;
    }
    return 0;
}
