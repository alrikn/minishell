/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** handle_redirection
*/

#include "my.h"
#include "struct.h"

/*
 ** the right node contains the destination
*/
int output_redirection(core_t *core, tree_t *node, int in_fd, int out_fd)
{
    if (node->type == OP_RSHIFT)
        return right_shift(core, node, in_fd, out_fd);
    if (node->type == OP_RAPPEND)
        return right_append(core, node, in_fd, out_fd);
    return 0;
}

int input_redirection(core_t *core, tree_t *node, int in_fd, int out_fd)
{
    if (node->type == OP_LSHIFT)
        return left_shift(core, node, in_fd, out_fd);
    if (node->type == OP_LAPPEND)
        return left_append(core, node, in_fd, out_fd);
    return 0;
}

/*
 ** if the right node does not contain a leaf node then invalid command
 **the big if statement is to ensure that if the output of the child
 has been redirected, (as in no input left for the redirection),
 the output gets mad
*/
int handle_redirection(core_t *core, tree_t *node, int in_fd, int out_fd)
{
    if (!node->right) {
        my_cooler_putstr("Missing name for redirect.\n");
        return -84;
    }
    if (!node->right->argv || node->left->type == OP_LSHIFT ||
    node->left->type == OP_RSHIFT || node->left->type == OP_RAPPEND ||
    node->left->type == OP_LAPPEND) {
        my_cooler_putstr("Ambiguous output redirect.\n");
        return -84;
    }
    if (node->type == OP_RSHIFT || node->type == OP_RAPPEND)
        return output_redirection(core, node, in_fd, out_fd);
    if (node->type == OP_LSHIFT || node->type == OP_LAPPEND)
        return input_redirection(core, node, in_fd, out_fd);
    return 0;
}
