/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** left_append
*/

#include "my.h"
#include "struct.h"
#include <fcntl.h>
#include <stdlib.h>

/*
** loops input in in a fd until the inputeed line is the one
this separator was called with
*/
void here_document_loop(int *pipefd, tree_t *node)
{
    long read_len = 0;
    char *line = NULL;
    size_t len = 0;
    char *delimiter = node->right->argv[0];

    while (true) {
        my_cooler_putstr("? ");
        read_len = getline(&line, &len, stdin);
        if (read_len < 0)
            break;
        if (my_strncmp(line, delimiter, strlen(delimiter)) == 0 &&
        line[my_strlen(delimiter)] == '\n')
            break;
        write(pipefd[1], line, read_len);
    }
    free(line);
}

int left_append(core_t *core, tree_t *node, int input, int output)
{
    int pipefd[2];

    if (pipe(pipefd) < 0)
        return -84;
    here_document_loop(pipefd, node);
    close(pipefd[WRITE]);
    execute_node(core, node->left, pipefd[READ], output);
    close(pipefd[WRITE]);
    return 0;
}
