/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** input_line_parser
*/

#include "my.h"
#include "stdio.h"
#include "struct.h"
#include <stdbool.h>
#include <stdlib.h>


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

static void count_metacharacter(const char *str, int *i, int *num_words)
{
    if ((str[*i] == '<' || str[*i] == '>' || str[*i] == '&' ||
        str[*i] == '|') && is_two_char_operator(str + *i)) {
            *num_words += 1;
            *i += 2;
        } else {
            *num_words += 1;
            *i += 1;
        }
}

static void handle_separators(const char *str, int *i, int *num_words)
{
    type_list_t type = 0;

    if (is_inhibitor(str[*i])) {
        type = determine_type(str[*i]);
        *i += 1;
        while (str[*i] && type != determine_type(str[*i]))
            *i += 1;
        if (type == determine_type(str[*i]))
            *i += 1;
        *num_words += 1;
        return;
    }
    if (is_metacharacter(str[*i])) {
        count_metacharacter(str, i, num_words);
    } else {
        while (str[*i] != '\0' && !is_space(str[*i]) &&
        !is_metacharacter(str[*i]) && !is_inhibitor(str[*i]))
            *i += 1;
        *num_words += 1;
    }
}

static int count_words(char const *str)
{
    int i = 0;
    int num_words = 0;

    if (!str)
        return 0;
    while (str[i] != '\0') {
        while (is_space(str[i]))
            i++;
        if (str[i] == '\0')
            break;
        handle_separators(str, &i, &num_words);
    }
    return num_words;
}

static char **extract_words(char const *str, char **array, argv_t *argv_struct)
{
    int i = 0;
    int word_index = 0;

    while (str[i] != '\0') {
        while (is_space(str[i]))
            i++;
        if (str[i] == '\0')
            break;
        if (is_inhibitor(str[i]) && !is_metacharacter(str[i])) {
            inhibitor_handle(str, &i, argv_struct, &word_index);
            continue;
        }
        if (is_metacharacter(str[i]) && !is_inhibitor(str[i])) {
            metacharacter_handle(str, &i, argv_struct, &word_index);
        } else
            copy_basic_words(&i, argv_struct, str, &word_index);
        if (argv_struct->types[word_index] == ERROR)
            return array;
    }
    return array;
}

static argv_t *initialize_argv(argv_t *argv_struct, int num_words)
{
    argv_struct = malloc(sizeof(argv_t) * 1);
    argv_struct->argv = malloc((num_words + 1) * sizeof(char *));
    argv_struct->types = malloc((num_words + 1) * sizeof(type_list_t));
    return argv_struct;
}

/*
** transform a str in an malloced array
** < << > >> | ' " ` && || ;
** example : "ls; cat main.c |grep env>>test" ->
0="ls" 1=";" 2="cat" 3="main.c" 4="|" 5="grep" 6="env" 7=">>" 8="test"
*/
argv_t *input_line_parser(char const *str)
{
    int num_words = count_words(str);
    argv_t *argv_struct = {0};

    if (!str)
        return NULL;
    argv_struct = initialize_argv(argv_struct, num_words);
    if (!argv_struct->argv || !str || !argv_struct->types)
        return NULL;
    for (int i = 0; i <= num_words; i++)
        argv_struct->types[i] = 0;
    argv_struct->argv[num_words] = NULL;
    if (num_words == 0)
        return argv_struct;
    argv_struct->argv = extract_words(str, argv_struct->argv, argv_struct);
    if (!argv_struct->argv) {
        free_argv_t(argv_struct);
        return NULL;
    }
    return argv_struct;
}
