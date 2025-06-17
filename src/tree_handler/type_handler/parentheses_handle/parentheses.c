/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parentheses
*/

#include "my.h"
#include "struct.h"
#include <sys/wait.h>
#include <unistd.h>

/*
** we assume the parentheses has been done and we are given the node paretnse;
** left is always best (only one direction)
*/
int handle_parenthese(core_t *core, tree_t *node, int input_fd, int output_fd)
{
    int fork_pid = fork();
    int signal_value;
    int status = 0;

    if (fork_pid < 0)
        return 84;
    if (fork_pid == 0) {
        if (input_fd != STDIN_FILENO) {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }
        if (output_fd != STDOUT_FILENO) {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }
        status = execute_node(core, node->left, STDIN_FILENO, STDOUT_FILENO);
        exit(status);
    } else
        waitpid(fork_pid, &signal_value, 0);
    return 0;
}
