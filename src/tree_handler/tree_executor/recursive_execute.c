/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** recusive_execute
*/

#include "my.h"
#include "struct.h"
#include <fcntl.h>

void handle_semicolon(core_t *core, tree_t *node, int input_fd, int output_fd)
{
    execute_node(core, node->left, STDIN_FILENO, STDOUT_FILENO);
    execute_node(core, node->right, STDIN_FILENO, STDOUT_FILENO);
}

/*
 ** once upon a time this was beautiful readable switch case
 but coding style happened
 **ths > >> < << are all sub leaf nodes, which means that
 if the right node is not a leaf node the the command is false
 **and and or are bonuses we will thinj about them later
*/
int execute_node(core_t *core, tree_t *node, int input_fd, int output_fd)
{
    int status = 0;

    if (!node)
        return -84;
    if (node->type == OP_NONE)
        return leaf_handler(core, node->argv, input_fd, output_fd);
    else if (!node->left && node->type != OP_SEMICOLON) {
        my_cooler_putstr("Invalid null command.\n");
        return -84;
    }
    if (node->type == OP_SEMICOLON)
        handle_semicolon(core, node, input_fd, output_fd);
    if (node->type == OP_LSHIFT || node->type == OP_RSHIFT ||
        node->type == OP_RAPPEND || node->type == OP_LAPPEND)
        return handle_redirection(core, node, input_fd, output_fd);
    if (node->type == OP_PIPE)
        handle_pipe(core, node, input_fd, output_fd);
    if (node->type == OP_AND || node->type == OP_OR)
        return -84;
    return status;
}
