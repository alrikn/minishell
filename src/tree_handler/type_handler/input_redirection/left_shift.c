/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** left_shift
*/

#include "my.h"

int left_shift(core_t *core, tree_t *node, int input, int output)
{
    int file_fd = -1;

    file_fd = open(node->right->argv[0], O_RDONLY);
    if (file_fd < 0)
        return -84;
    execute_node(core, node->left, file_fd, output);
    close(file_fd);
    return 0;
}
