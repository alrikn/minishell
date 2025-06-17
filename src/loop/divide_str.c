/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** divide_str
*/

#include "my.h"
#include "struct.h"

static void *my_memcpy(void *dest, const void *src, size_t n)
{
    char *d = dest;
    const char *s = src;

    for (size_t i = 0; i < n; i++)
        d[i] = s[i];
    return dest;
}

static bool is_space(char letter)
{
    return (letter == ' ' || letter == '\t' || letter == '\n');
}

static bool is_metacharacter(char c)
{
    if (c == '<' || c == '>' || c == '|' || c == '&' || c == ';' ||
    c == '(' || c == ')')
        return true;
    return false;
}

static bool is_two_char_operator(const char *s)
{
    if (s[0] == '\0' || s[1] == '\0')
        return false;
    if ((s[0] == '<' && s[1] == '<') || (s[0] == '>' && s[1] == '>') ||
    (s[0] == '&' && s[1] == '&') || (s[0] == '|' && s[1] == '|'))
        return true;
    return false;
}

void metacharacter_handle(const char *str, int *i,
    argv_t *argv_struct, int *word_index)
{
    int token_len = 1;
    char *token = NULL;

    if ((str[*i] == '<' || str[*i] == '>' || str[*i] == '&' || str[*i] == '|')
    && is_two_char_operator(str + *i)) {
        token_len = 2;
    }
    token = malloc(token_len + 1);
    if (!token) {
        return;
    }
    my_memcpy(token, str + *i, token_len);
    token[token_len] = '\0';
    argv_struct->argv[*word_index] = token;
    argv_struct->types[*word_index] = NORM;
    *word_index += 1;
    *i += token_len;
}

/*
** asssuming we are already on a inhibitor
*/
void inhibitor_handle(const char *str, int *i, argv_t *argv_struct,
    int *word_index)
{
    type_list_t type = determine_type(str[*i]);
    int token_len = 0;
    char *result = NULL;

    *i += 1;
    result = inhibitor_parse(type, str, i, &token_len);
    if (result == NULL) {
        argv_struct->types[*word_index] = ERROR;
        argv_struct->argv[*word_index] = NULL;
        return;
    }
    argv_struct->types[*word_index] = type;
    argv_struct->argv[*word_index] = result;
    *word_index += 1;
    if (str[*i])
        *i += 1;
}

argv_t *copy_basic_words(int *i, argv_t *argv_struct,
    char const *str, int *word_i)
{
    int end = 0;
    int word_len = 0;
    char *word = NULL;
    int start = *i;

    while (str[*i] != '\0' && !is_space(str[*i]) && !is_metacharacter(str[*i])
        && !is_inhibitor(str[*i]))
        (*i)++;
    end = *i;
    word_len = end - start;
    word = malloc(word_len + 1);
    if (!word)
        return NULL;
    my_memcpy(word, str + start, word_len);
    word[word_len] = '\0';
    argv_struct->argv[*word_i] = word;
    argv_struct->types[*word_i] = NORM;
    (*word_i)++;
    return argv_struct;
}
