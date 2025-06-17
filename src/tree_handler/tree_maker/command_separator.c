/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** command_separator
*/

#include "my.h"
#include "struct.h"
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

int argc_counter(char **array)
{
    int i = 0;

    if (!array)
        return 0;
    while (array[i])
        i++;
    return i;
}

static int allocator(argv_t **new_struct_ptr, int end, int start)
{
    int new_len = end - start;

    *new_struct_ptr = malloc(sizeof(argv_t));
    (*new_struct_ptr)->argv = malloc((new_len + 1) * sizeof(char *));
    (*new_struct_ptr)->types = malloc(sizeof(type_list_t) * (new_len + 1));
    return new_len;
}

/*
 ** copies part of an array
 ** if end = -1 go until the end of array
*/
argv_t *duplicate_argv_segment(argv_t *argv_struct, int start, int end)
{
    int argc = argc_counter(argv_struct->argv);
    int new_len = 0;
    argv_t *new_struct = NULL;

    if (start < 0 || start >= argc)
        return NULL;
    if (end < 0 || end > argc)
        end = argc;
    if (start > end)
        return NULL;
    new_len = allocator(&new_struct, end, start);
    if (!new_struct || !new_struct->argv)
        return NULL;
    for (int i = 0; i < new_len; i++) {
        new_struct->types[i] = argv_struct->types[start + i];
        new_struct->argv[i] = my_strdup(argv_struct->argv[start + i]);
    }
    new_struct->argv[new_len] = NULL;
    new_struct->types[new_len] = NONE;
    return new_struct;
}

static tree_t *initialize_node(void)
{
    tree_t *node = NULL;

    node = malloc(sizeof(tree_t));
    if (!node)
        return NULL;
    node->argv_struct = NULL;
    node->error_occured = false;
    node->left = NULL;
    node->right = NULL;
    node->type = OP_NONE;
    return node;
}

static tree_t *make_branch_node(tree_t *node, argv_t *argv_struct,
    int last_pos, int i)
{
    argv_t *left = NULL;
    argv_t *right = NULL;

    left = duplicate_argv_segment(argv_struct, 0, last_pos);
    right = duplicate_argv_segment(argv_struct, last_pos + 1, -1);
    node->type = MY_OPERAT[i].type;
    node->left = recursive_parse(left);
    node->right = recursive_parse(right);
    node->is_leaf = false;
    free_argv_t(left);
    free_argv_t(right);
    return node;
}

/*
** if its true that means we have nothing to skip
** if false we do have stuff to skip so continue as usual
*/
static bool skip_decision(tree_t *node, char **argv, int *j)
{
    bool result;

    if (my_strcmp(argv[*j], ")") == 0) {
        result = skip_parenthese(node, argv, j);
        return result;
    }
    return false;
}

/*
** goes gfrom last to first
** if there it returns true that means thers is nothing but parenthes
*/
static bool last_pos_update(int *last_pos, argv_t *argv_struct,
    const char *tar_sym, tree_t *node)
{
    int argc = argc_counter(argv_struct->argv);
    bool result;

    for (int j = argc - 1; j >= 0; j--) {
        if (my_strcmp(argv_struct->argv[j], "(") == 0) {
            my_cooler_putstr("Too many ('s.\n");
            node->error_occured = true;
            break;
        }
        result = skip_decision(node, argv_struct->argv, &j);
        if (node->error_occured)
            break;
        if (result)
            return true;
        if (j >= 0 && my_strcmp(argv_struct->argv[j], tar_sym) == 0)
            *last_pos = j;
    }
    return false;
}

/*
** the last returns leaf nodes and the middle return for branch nodes
*/
tree_t *recursive_parse(argv_t *av_stru)
{
    int last_pos = -1;
    tree_t *nod = NULL;
    bool parent = false;

    if (!av_stru || !av_stru->argv || !av_stru->argv[0]) {
        return NULL;
    }
    nod = initialize_node();
    for (int i = 0; MY_OPERAT[i].symbol != NULL; i++) {
        parent = last_pos_update(&last_pos, av_stru, MY_OPERAT[i].symbol, nod);
        if (nod->error_occured)
            return nod;
        if (parent)
            return deal_with_paren(nod, av_stru, last_pos);
        if (last_pos != -1)
            return make_branch_node(nod, av_stru, last_pos, i);
    }
    nod->argv_struct = duplicate_argv_segment(av_stru, 0, -1);
    nod->is_leaf = true;
    return nod;
}

/*
 ** i assume that everything is already organized in argv and argc
 and that argv is malloced
*/
tree_t *tree_parser(core_t *core, argv_t *argv_struct)
{
    tree_t *head = NULL;

    core->tree.parse_error = false;
    if (!argv_struct || !argv_struct->argv)
        return NULL;
    if (entrenchment_error_finder(core, argv_struct->argv))
        return NULL;
    head = recursive_parse(argv_struct);
    if (!head) {
        my_cooler_putstr("root is null\n");
    }
    return head;
}
