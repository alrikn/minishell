/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** background_handle
*/

#include "my.h"
#include "struct.h"

int back_handle(core_t *core, tree_t *node, int in, int out)
{
    bool background = core->job.is_background;

    if (node->left) {
        core->job.is_background = true;
        execute_node(core, node->left, in, out);
    }
    core->job.is_background = background;
    if (node->right) {
        execute_node(core, node->right, in, out);
    }
    core->job.is_background = false;
    return 0;
}
