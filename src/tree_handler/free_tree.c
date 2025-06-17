/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** free_tree
*/

#include "my.h"

void free_argv_t(argv_t *argv_struct)
{
    if (!argv_struct)
        return;
    if (argv_struct->argv)
        free_array(argv_struct->argv);
    if (argv_struct->types)
        free(argv_struct->types);
    free(argv_struct);
    argv_struct = NULL;
}

int recursive_free(tree_t *node)
{
    tree_t *next;

    if (!node)
        return 84;
    if (node->left) {
        next = node->left;
        recursive_free(next);
    }
    if (node->right) {
        next = node->right;
        recursive_free(next);
    }
    if (node->argv_struct)
        free_argv_t(node->argv_struct);
    free(node);
    return 0;
}

/*
 ** free the entire tree root included
*/
int free_tree(tree_t *root)
{
    tree_t *temp = root;

    if (recursive_free(temp) == 84) {
        return 84;
    }
    return 0;
}
