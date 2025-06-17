/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** redirector
*/

#include "my.h"
#include "struct.h"

int recursive_error_check(core_t *core, tree_t *node)
{
    if (!node)
        return 84;
    if (node->error_occured) {
        core->tree.parse_error = true;
        return 84;
    }
    if (node->left)
        recursive_error_check(core, node->left);
    if (node->right)
        recursive_error_check(core, node->right);
    node->done = true;
    return 0;
}
