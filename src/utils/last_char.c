/*
** EPITECH PROJECT, 2025
** bsminishell1
** File description:
** returns everything after delimeter
** it does malloc the result so watch out
*/

#include <stdlib.h>
#include <unistd.h>

static void my_charswap(char *a, char *b)
{
    int temp = *a;

    *a = *b;
    *b = temp;
}

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

static char *my_fake_strdup(char const *src)
{
    int len = my_strlen(src);
    char *dest = malloc(len + 1);

    if (dest == NULL) {
        return NULL;
    }
    for (int n = 0; n < len; n++) {
        dest[n] = src[n];
    }
    dest[len] = '\0';
    return dest;
}

static char *my_fake_revstr(char *str)
{
    char *str_end = str;
    char *str_start = str;

    if (!str)
        return NULL;
    while (str_end[1] != '\0') {
        str_end++;
    }
    for (; str_start < str_end; str_start++) {
        my_charswap(str_start, str_end);
        str_end--;
    }
    return str;
}

char *last_char(const char *str, char character)
{
    char *rev = NULL;
    int len = my_strlen(str);
    int i = 0;
    char *result = NULL;

    if (!str)
        return NULL;
    rev = my_fake_strdup(str);
    rev = my_fake_revstr(rev);
    while (rev[i] && rev[i] != character)
        i++;
    if (rev[i] != character)
        return my_fake_revstr(rev);
    rev = my_fake_revstr(rev);
    result = my_fake_strdup(rev + (len - (i)));
    free(rev);
    return result;
}
