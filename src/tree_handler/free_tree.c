/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** free_tree
*/

#include "my.h"

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
    if (node->argv)
        free_array(node->argv);
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
