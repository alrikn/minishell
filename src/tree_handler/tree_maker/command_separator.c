/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** command_separator
*/

#include "my.h"
#include "struct.h"

int argc_counter(char **array)
{
    int i = 0;

    while (array[i])
        i++;
    return i;
}

/*
 ** copies part of an array
 ** if end = -1 go until the end of array
*/
char **duplicate_argv_segment(char **argv, int start, int end)
{
    int argc = argc_counter(argv);
    int new_len = 0;
    char **new_argv = NULL;

    if (start < 0 || start >= argc)
        return NULL;
    if (end < 0 || end > argc)
        end = argc;
    if (start > end)
        return NULL;
    new_len = end - start;
    new_argv = malloc((new_len + 1) * sizeof(char *));
    if (!new_argv)
        return NULL;
    for (int i = 0; i < new_len; i++) {
        new_argv[i] = my_strdup(argv[start + i]);
    }
    new_argv[new_len] = NULL;
    return new_argv;
}

static tree_t *make_leaf(tree_t *node, char **argv, int last_pos, int i)
{
    char **left = NULL;
    char **right = NULL;

    left = duplicate_argv_segment(argv, 0, last_pos);
    right = duplicate_argv_segment(argv, last_pos + 1, -1);
    node = malloc(sizeof(tree_t));
    node->type = MY_OPERATORS[i].type;
    node->argv = NULL;
    node->left = recursive_parse(left);
    node->right = recursive_parse(right);
    node->is_leaf = false;
    free_array(left);
    free_array(right);
    return node;
}

static int last_pos_update(int last_pos, char **argv, const char *tar_sym)
{
    for (int j = 0; argv[j]; j++) {
        if (my_strcmp(argv[j], tar_sym) == 0)
            last_pos = j;
    }
    return last_pos;
}

tree_t *recursive_parse(char **argv)
{
    int last_pos = -1;
    tree_t *node = NULL;
    const char *target_symbol;

    if (!argv || !argv[0])
        return NULL;
    for (int i = 0; MY_OPERATORS[i].symbol != NULL; i++) {
        target_symbol = MY_OPERATORS[i].symbol;
        last_pos = last_pos_update(last_pos, argv, target_symbol);
        if (last_pos != -1)
            return make_leaf(node, argv, last_pos, i);
    }
    node = malloc(sizeof(tree_t));
    node->type = OP_NONE;
    node->argv = duplicate_argv_segment(argv, 0, -1);
    node->left = NULL;
    node->right = NULL;
    node->is_leaf = true;
    return node;
}

/*
 ** i assume that everything is already organized in argv and argc
 and that argv is malloced
*/
tree_t *tree_parser(char **argv)
{
    tree_t *head = recursive_parse(argv);

    if (!head)
        my_cooler_putstr("root is null\n");
    return head;
}
