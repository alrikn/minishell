/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** right_shift
*/

#include "my.h"
#include "struct.h"
#include <fcntl.h>
#include <stdbool.h>

void reset_sub_input(core_t *core)
{
    core->sub_input.env = NULL;
    core->sub_input.argv = NULL;
    core->sub_input.path = NULL;
    core->sub_input.command = NULL;
}

/*
 **if change input is null then pipe_input does not matter
 ** takes the input and put it in file. destroys previous text
*/
int right_shift(core_t *core, tree_t *node, int input, int output)
{
    int file_fd = -1;

    file_fd = open(node->right->argv_struct->argv[0],
    O_CREAT | O_WRONLY | O_TRUNC, 0664);
    if (file_fd < 0)
        return -84;
    execute_node(core, node->left, input, file_fd);
    close(file_fd);
    return 0;
}
