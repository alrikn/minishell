/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** this file takes the env and the path + arguments and executes it
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include "my.h"
#include "struct.h"
#include <sys/stat.h>

/*
 ** if execve fails, smth has gone very wrong and we complain about it
 ** valgrind will also complain about memory leaks, but they are fake
 because we deal with them outside the fork
*/
static void fork_child(char *path, char **command, char **env, core_t *core)
{
    execve(path, command, env);
    my_cooler_putstr(path);
    my_cooler_putstr(": Exec format error. Binary file not executable.\n");
    core->exit.last_failed = true;
    exit(84);
}

static void fault(int status)
{
    if (WIFSIGNALED(status) == true) {
        my_cooler_putstr(strsignal(WTERMSIG(status)));
        my_cooler_putstr(" (core dumped)\n");
    }
}

/*
 ** this function shoul only be called if the file is executable
 ** it handles the fork and updates the last value received (echo $?)
*/
int execve_handler(char *path, char **command, char **env, core_t *core)
{
    int signal_value = 0;
    pid_t p = fork();

    if (p == 0)
        fork_child(path, command, env, core);
    else if (p > 0) {
        waitpid(p, &signal_value, 0);
        core->exit.last_value = WEXITSTATUS(signal_value);
    }
    if (signal_value != 0)
        fault(signal_value);
    return 0;
}

/*
 ** makes a copy of argv so that i can play around with it without
 worrying about memory leaks or invalid memory reads
*/
static char **argument_parser(char **argv)
{
    char **arguments = NULL;
    int i = 0;

    if (!argv)
        return NULL;
    while (argv[i])
        i++;
    arguments = malloc(sizeof(char *) * (i + 1));
    for (int j = 0; j < i; j++) {
        arguments[j] = my_strdup(argv[j]);
    }
    arguments[i] = NULL;
    return arguments;
}

int memory_leak_handle(char *path, char *name, char **env, char **arguments)
{
    free(path);
    free(name);
    free_array(env);
    free_array(arguments);
    return 84;
}

static int is_directory(const char *path)
{
    struct stat file_stat;

    if (stat(path, &file_stat) != 0) {
        perror("stat");
        return 0;
    }
    return S_ISDIR(file_stat.st_mode);
}

/*
 ** if path is null then it means that the input is false and it does not exist
 ** otherwise we launch it one we checked that it is executable and not a
 directory
*/
static int check_if_executable(char *path, core_t *core, char **argv)
{
    if (!path) {
        my_cooler_putstr(argv[0]);
        my_cooler_putstr(": Command not found.\n");
        core->exit.last_failed = true;
        return 1;
    }
    if (access(path, X_OK) != 0 || is_directory(path)) {
        my_cooler_putstr(path);
        my_cooler_putstr(": Permission denied.\n");
        core->exit.last_failed = true;
        return 1;
    }
    return 0;
}

/*
 ** this function will handle everything that is not a builtin
 ** env is malloced
*/
int binary_handler(char **argv, char **env, core_t *core)
{
    char **arguments = argument_parser(argv);
    char *path = find_path(argv, core);
    char *command_name = last_char(path, '/');

    if (check_if_executable(path, core, argv) == 1) {
        return memory_leak_handle(path, command_name, env, arguments);
    }
    free(arguments[0]);
    arguments[0] = command_name;
    execve_handler(path, arguments, env, core);
    free(path);
    free_array(arguments);
    free_array(env);
    return 0;
}
