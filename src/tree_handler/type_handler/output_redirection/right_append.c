/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** right_append
*/

#include "my.h"
#include <fcntl.h>

int right_append(core_t *core, tree_t *node, int input, int output)
{
    int file_fd = -1;

    file_fd = open(node->right->argv[0], O_CREAT | O_WRONLY | O_APPEND, 0664);
    if (file_fd < 0)
        return -84;
    execute_node(core, node->left, input, file_fd);
    close(file_fd);
    return 0;
}
