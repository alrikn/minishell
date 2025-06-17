/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** pipe_reirection
*/

#include "my.h"


static void left_fork(core_t *core, tree_t *node, int input_fd, int *pipe_fd)
{
    close(pipe_fd[READ]);
    execute_node(core, node->left, input_fd, pipe_fd[WRITE]);
    close(pipe_fd[WRITE]);
    exit(EXIT_SUCCESS);
}

static void right_fork(core_t *core, tree_t *node, int *pipe_fd, int output_fd)
{
    close(pipe_fd[WRITE]);
    execute_node(core, node->right, pipe_fd[READ], output_fd);
    close(pipe_fd[READ]);
    exit(EXIT_SUCCESS);
}

static int pipe_fork(core_t *core, tree_t *node, int input_fd, int output_fd)
{
    int pipe_fd[2];
    int left_pid = -1;
    int right_pid = -1;

    pipe(pipe_fd);
    left_pid = fork();
    if (left_pid < 0)
        return 84;
    if (left_pid == 0)
        left_fork(core, node, input_fd, pipe_fd);
    right_pid = fork();
    if (right_pid < 0)
        return 84;
    if (right_pid == 0)
        right_fork(core, node, pipe_fd, output_fd);
    close(pipe_fd[READ]);
    close(pipe_fd[WRITE]);
    waitpid(left_pid, NULL, 0);
    waitpid(right_pid, NULL, 0);
    return 0;
}

/*
 **it forks because otherwise on big commands pipefd fill and gets locked
 **the big if statement is to ensure that if the output of the child
 has been redirected, (as in no input left for the pipe), the output gets mad
*/
int handle_pipe(core_t *core, tree_t *node, int input_fd, int output_fd)
{
    if (!node->right || !node->left) {
        my_cooler_putstr("Invalid null command.\n");
        return 84;
    }
    if (node->left->type == OP_LSHIFT || node->left->type == OP_RSHIFT ||
    node->left->type == OP_RAPPEND || node->left->type == OP_LAPPEND) {
        my_cooler_putstr("Ambiguous output redirect.\n");
        return 84;
    }
    return pipe_fork(core, node, input_fd, output_fd);
}
