/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** redirector
*/

#include "my.h"

int recursive_execute(tree_t *node, int *pipefd)
{
    if (!node)
        return 84;
    if (node->left)
        recursive_execute(node->left, pipefd);
    if (node->right)
        recursive_execute(node->right, pipefd);
    node->done = true;
    return 0;
}
