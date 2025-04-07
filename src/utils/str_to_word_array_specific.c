/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** str_to_word_array_specific
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

static bool is_letter(char letter, char spec_letter)
{
    if (spec_letter == ' ') {
        if (letter == ' ' || letter == '\t' || letter == '\n')
            return true;
        else
            return false;
    } else {
        if (letter == spec_letter)
            return true;
        else
            return false;
    }
}

static int count_words(char const *str, char spec_letter)
{
    int i = 0;
    int num_words = 0;

    if (!str)
        return 0;
    while (str[i] != '\0') {
        while (str[i] != '\0' && is_letter(str[i], spec_letter))
            i++;
        if (str[i] == '\0')
            break;
        num_words++;
        while (str[i] != '\0' && !is_letter(str[i], spec_letter))
            i++;
    }
    return num_words;
}

static char *copy_words(int *i, char **array, char const *str, char spec_let)
{
    int end = 0;
    int word_len = 0;
    char *word = NULL;
    int start = 0;

    start = *i;
    while (str[*i] != '\0' && !is_letter(str[*i], spec_let))
        *i += 1;
    end = *i;
    word_len = end - start;
    word = malloc(word_len + 1);
    if (!word)
        return NULL;
    my_memcpy(word, str + start, word_len);
    word[word_len] = '\0';
    return word;
}

static char **extract_words(char const *str, char **array, char spec_letter)
{
    int i = 0;
    int word_index = 0;
    char *word = NULL;

    while (str[i] != '\0') {
        while (str[i] != '\0' && is_letter(str[i], spec_letter))
            i++;
        if (str[i] == '\0')
            break;
        word = copy_words(&i, array, str, spec_letter);
        if (word == NULL)
            return NULL;
        array[word_index] = word;
        word_index += 1;
    }
    return array;
}

char **my_str_to_word_array_specific(char const *str, char spec_letter)
{
    int num_words = count_words(str, spec_letter);
    char **array = NULL;

    if (num_words == 0)
        return NULL;
    array = malloc((num_words + 1) * sizeof(char *));
    if (!array || !str)
        return NULL;
    array[num_words] = NULL;
    if (num_words == 0)
        return array;
    array = extract_words(str, array, spec_letter);
    return array;
}
