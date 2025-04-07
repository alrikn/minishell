/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** leaf_execution
*/

#include "my.h"

/*
 ** if execve fails, smth has gone very wrong and we complain about it
 ** valgrind will also complain about memory leaks, but they are fake
 because we deal with them outside the fork
*/
static void fork_child(core_t *core, int input_fd, int output_fd)
{
    if (input_fd != STDIN_FILENO) {
        dup2(input_fd, STDIN_FILENO);
        close(input_fd);
    }
    if (output_fd != STDOUT_FILENO) {
        dup2(output_fd, STDOUT_FILENO);
        close(output_fd);
    }
    execve(core->sub_input.path, core->sub_input.command, core->sub_input.env);
    my_cooler_putstr(core->sub_input.path);
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
static int execve_handler(core_t *core, int input_fd, int output_fd)
{
    int signal_value = 0;
    pid_t p = fork();

    if (p == 0)
        fork_child(core, input_fd, output_fd);
    else if (p > 0) {
        waitpid(p, &signal_value, 0);
        core->exit.last_value = WEXITSTATUS(signal_value);
    }
    if (input_fd != STDIN_FILENO)
        close(input_fd);
    if (output_fd != STDOUT_FILENO)
        close(output_fd);
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

static int mem_leak_hand(char *path, char *name, char **env, char **arguments)
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
 **if path is null then it means that the input is false and it does not exist
 **otherwise we launch it one we checked that it is executable and not a
 directory
*/
static int check_if_executable(char *path, core_t *core, char **argv)
{
    if (!path) {
        my_cooler_putstr(argv[0]);
        my_cooler_putstr(": Command not found.\n");
        core->exit.last_failed = true;
        return 84;
    }
    if (access(path, X_OK) != 0 || is_directory(path)) {
        my_cooler_putstr(path);
        my_cooler_putstr(": Permission denied.\n");
        core->exit.last_failed = true;
        return 84;
    }
    return 0;
}

/*
 ** this function will handle everything that is not a builtin
 ** everything should be in the core->sub_input
*/
int leaf_executor(core_t *core, int pipe_to_child, int pipe_from_child)
{
    char *com_name = NULL;

    core->sub_input.command = argument_parser(core->sub_input.argv);
    core->sub_input.path = find_path(core->sub_input.argv, core);
    com_name = last_char(core->sub_input.path, '/');
    if (check_if_executable(core->sub_input.path, core,
    core->sub_input.argv) != 0) {
        return mem_leak_hand(core->sub_input.path, com_name,
        core->sub_input.env, core->sub_input.command);
    }
    free(core->sub_input.command[0]);
    core->sub_input.command[0] = com_name;
    execve_handler(core, pipe_to_child, pipe_from_child);
    free(core->sub_input.path);
    free_array(core->sub_input.command);
    free_array(core->sub_input.env);
    return core->exit.last_value;
}
