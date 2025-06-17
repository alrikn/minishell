/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** recusive_execute
*/

#include "my.h"
#include "struct.h"
#include <fcntl.h>
#include <stdio.h>

int handle_semicolon(core_t *core, tree_t *node, int input_fd, int output_fd)
{
    if (node->left)
        execute_node(core, node->left, STDIN_FILENO, STDOUT_FILENO);
    if (node->right)
        return execute_node(core, node->right, STDIN_FILENO, STDOUT_FILENO);
    return 0;
}

static bool error_message_execute(tree_t *nod)
{
    if (!nod || (nod->type != OP_NONE && !nod->left &&
    nod->type != OP_SEMICOLON)) {
        my_cooler_putstr("Invalid null command.\n");
        return true;
    }
    return false;
}

static int handle_background_option(core_t *core, tree_t *node,
    int input_fd, int output_fd)
{
    if (node->type == OP_OR || node->type == OP_AND)
        return handle_or_and(core, node, input_fd, output_fd);
    if (node->type == OP_BG_S)
        return back_handle(core, node, input_fd, output_fd);
    return 84;
}

/*
** back to being a beautiflu switch case
*/
static int switch_case_parse(core_t *core, tree_t *node,
    int input_fd, int output_fd)
{
    switch (node->type) {
        case OP_NONE:
            return leaf_handler(core, node->argv_struct, input_fd, output_fd);
        case OP_SEMICOLON:
            return handle_semicolon(core, node, input_fd, output_fd);
        case OP_LSHIFT:
        case OP_RSHIFT:
        case OP_RAPPEND:
        case OP_LAPPEND:
            return handle_redirection(core, node, input_fd, output_fd);
        case OP_PAREN:
            return handle_parenthese(core, node, input_fd, output_fd);
        case OP_PIPE:
            return handle_pipe(core, node, input_fd, output_fd);
        default:
            return handle_background_option(core, node, input_fd, output_fd);
    }
}

/*
 **ths > >> < << are all sub leaf nodes, which means that
 if the right node is not a leaf node the the command is false
 **and and or are bonuses we will thinj about them later
*/
int execute_node(core_t *core, tree_t *node, int input_fd, int output_fd)
{
    if (error_message_execute(node))
        return -84;
    return switch_case_parse(core, node, input_fd, output_fd);
}
