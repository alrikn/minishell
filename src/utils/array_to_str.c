/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** array_to_str
*/

#include <stdlib.h>

static int my_strlen(char const *str)
{
    char const *ptr = str;
    int len = 0;

    if (!str)
        return 0;
    while (*ptr != '\0') {
        ptr++;
        len++;
    }
    return (len);
}

static long total_len_calculator(char **array)
{
    long len = 0;

    if (!array)
        return 0;
    for (long i = 0; array[i]; i++)
        len += my_strlen(array[i]) + 1;
    return len;
}

/*
** the str is malloced and the input is expected to be null terminated
** argv { 1 = "one" 2 = "two"} becomes str = "one two"
*/
char *array_to_str(char **array)
{
    char *str;
    long len = total_len_calculator(array);
    long abs_index = 0;

    if (!array || len == 0)
        return NULL;
    str = malloc(sizeof(char) * len);
    if (!str)
        return NULL;
    for (long i = 0; array[i]; i++) {
        for (int j = 0; array[i][j]; j++) {
            str[abs_index] = array[i][j];
            abs_index++;
        }
        str[abs_index] = ' ';
        abs_index++;
    }
    str[len - 1] = '\0';
    return str;
}
