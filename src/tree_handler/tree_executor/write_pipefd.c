/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** write_pipefd
*/

#include "my.h"

/*
 **writes the content of pipefd to the stdout
*/
void write_pipefd(int *pipefd)
{
    char buffer[1024];
    long n;

    n = read(pipefd[READ], buffer, sizeof(buffer));
    while (n > 0) {
        write(STDOUT_FILENO, buffer, n);
        n = read(pipefd[READ], buffer, sizeof(buffer));
    }
}
