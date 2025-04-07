/*
** EPITECH PROJECT, 2025
** bsminishell1
** File description:
** str_to_word_array
*/

#include "stdio.h"
#include <stdbool.h>
#include <stdlib.h>


static void *my_memcpy(void *dest, const void *src, size_t n)
{
    char *d = dest;
    const char *s = src;

    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dest;
}

static bool is_space(char letter)
{
    if (letter == ' ' || letter == '\t' || letter == '\n')
        return true;
    else
        return false;
}

int count_words(char const *str)
{
    int i = 0;
    int num_words = 0;

    if (!str)
        return 0;
    while (str[i] != '\0') {
        while (str[i] != '\0' && is_space(str[i]))
            i++;
        if (str[i] == '\0')
            break;
        num_words++;
        while (str[i] != '\0' && !is_space(str[i]))
            i++;
    }
    return num_words;
}

char **copy_words(int *i, char **array, char const *str, int *word_i)
{
    int end = 0;
    int word_len = 0;
    char *word = NULL;
    int start = 0;

    start = *i;
    while (str[*i] != '\0' && !is_space(str[*i]))
        *i += 1;
    end = *i;
    word_len = end - start;
    word = malloc(word_len + 1);
    if (!word)
        return NULL;
    my_memcpy(word, str + start, word_len);
    word[word_len] = '\0';
    array[*word_i] = word;
    *word_i += 1;
    return array;
}

char **extract_words(char const *str, char **array)
{
    int i = 0;
    int word_index = 0;

    while (str[i] != '\0') {
        while (str[i] != '\0' && is_space(str[i]))
            i++;
        if (str[i] == '\0')
            break;
        array = copy_words(&i, array, str, &word_index);
        if (array == NULL)
            return NULL;
    }
    return array;
}

char **my_str_to_word_array(char const *str)
{
    int num_words = count_words(str);
    char **array = malloc((num_words + 1) * sizeof(char *));

    if (!array || !str)
        return NULL;
    array[num_words] = NULL;
    if (num_words == 0)
        return array;
    array = extract_words(str, array);
    return array;
}
