/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** prompt_loop
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "my.h"
#include "struct.h"

void free_everything(core_t *core, char *input)
{
    if (input)
        free(input);
    if (core->input.argv)
        free_array(core->input.argv);
    if (core->head)
        free_list(core->head);
}

/*
 ** this resetss the flags to ensure that loops do'nt interfere with each other
 ** the flag boolean is set to true if we are calling one of the builtins
 ** last_failed if the builtin that we called in the loop failed
*/
void flag_reset(core_t *core)
{
    core->com.flag = false;
    core->exit.last_failed = false;
}

static int flag_catch(core_t *core, char **argv)
{
    char *list_of_builtin[] = {"env", "cd", "setenv", "unsetenv", "echo",
    NULL};
    int (*list_of_function[])(core_t *, char **argv) = {print_env, cd_handler,
    setenv_direct, unsetenv_direct, echo_handler};
    int i = 0;

    while (list_of_builtin[i]) {
        if (argv && argv[0] && my_strcmp(list_of_builtin[i], argv[0]) == 0) {
            core->com.flag = true;
            return list_of_function[i](core, argv);
        }
        i++;
    }
    return 0;
}

/*
 ** this checks the flags(cd, env, setenv, unsetenv, exit)
 ** exit is checked separately, because it is the only builtin
 that is not linked
 to an actual function
*/
int check_system_commands(core_t *core, char **argv)
{
    int len = my_strlen(argv[0]);

    flag_reset(core);
    if (len == 0)
        return 1;
    if (len == 4 &&
    my_strncmp(argv[0], "exit", my_strlen("exit")) == 0) {
        core->com.exit = true;
        return 0;
    }
    if (flag_catch(core, argv) != 0) {
        core->exit.last_failed = true;
    }
    return 0;
}

/*
 ** we make argc and argv
 ** argv is malloced so be careful
*/
static void input_maker(core_t *core, char *input)
{
    int i = 0;

    core->input.argv = my_str_to_word_array(input);
    while (core->input.argv[i])
        i++;
    core->input.argc = i;
}

int handle_argv(core_t *core, char *input)
{
    input_maker(core, input);
    core->tree.root = tree_parser(core->input.argv);
    execute_node(core, core->tree.root, STDIN_FILENO, STDOUT_FILENO);
    free_tree(core->tree.root);
    free_array(core->input.argv);
    core->input.argv = NULL;
    core->tree.root = NULL;
    return 0;
}

/*
 to skip the spaces so that i know when i should skip the line cus no command
*/
static char *format_input(char *line)
{
    int i = 0;
    char *trimmed = line;

    while (*trimmed == ' ' || *trimmed == '\t')
        trimmed++;
    while (trimmed[i] && trimmed[i] != '\n') {
        i++;
    }
    if (trimmed[i] == '\n')
        trimmed[i] = '\0';
    return trimmed;
}

/*
 ** if this while loop breaks the program stops
 ** the rushed_exit boolean is for ctrl d, which will make the program return
 the last exit value
*/
void main_loop(core_t *core)
{
    char *input = NULL;
    size_t len = 0;
    ssize_t nread = 0;
    char *trimmed = NULL;

    while (core->com.exit == false) {
        my_cooler_putstr("$> ");
        nread = getline(&input, &len, stdin);
        if (nread == -1) {
            core->exit.rushed_exit = true;
            break;
        }
        trimmed = format_input(input);
        if (nread == 1 || nread == 0 || trimmed[0] == '\0')
            continue;
        handle_argv(core, input);
    }
    free_everything(core, input);
}
