/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** and_or
*/

#include "my.h"
#include "struct.h"

int handle_or(core_t *core, tree_t *node, int input_fd, int output_fd)
{
    if (execute_node(core, node->left, input_fd, output_fd) == 0 ||
    execute_node(core, node->right, input_fd, output_fd) == 0)
        return 0;
    return 1;
}

int handle_and(core_t *core, tree_t *node, int input_fd, int output_fd)
{
    if (execute_node(core, node->left, input_fd, output_fd) == 0 &&
    execute_node(core, node->right, input_fd, output_fd) == 0)
        return 0;
    return 1;
}

int handle_or_and(core_t *core, tree_t *node,
    int input_fd, int output_fd)
{
    if (node->type == OP_OR) {
        core->exit.last_value = handle_or(core, node, input_fd, output_fd);
        return core->exit.last_value;
    }
    if (node->type == OP_AND) {
        core->exit.last_value = handle_and(core, node, input_fd, output_fd);
        return core->exit.last_value;
    }
    return 84;
}
