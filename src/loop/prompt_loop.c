/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** prompt_loop
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "my.h"
#include "struct.h"

void free_everything(core_t *core, char *input)
{
    if (core->input.argv_struct)
        free_argv_t(core->input.argv_struct);
    if (core->head)
        free_list(core->head);
    if (core->alias_head)
        free_alias_list(core->alias_head);
    if (core->history.file_dp)
        fclose(core->history.file_dp);
    if (core->history.hist_head)
        free_history(core->history.hist_head);
    free_jobs(core->job.job_head);
}

/*
** we make argc and argv
** argv is malloced so be careful
*/
static void input_maker(core_t *core, char *input)
{
    int i = 0;

    core->input.argv_struct = input_line_parser(input);
    if (!core->input.argv_struct || !core->input.argv_struct->argv)
        return;
    while (core->input.argv_struct->argv[i])
        i++;
    core->input.argc = i;
}

/*
** we take a the argv, parse it to a syntax tree,
** verify everything is correct
** execute the tree in order (redirections and everything)
** and then free everything
*/
int handle_argv(core_t *core, char *input)
{
    input_maker(core, input);
    history_handle(core, core->input.argv_struct);
    if (core->input.argv_struct && !inhibitor_error(core->input.argv_struct)
    && argc_counter(core->input.argv_struct->argv) != 0) {
        core->tree.root = tree_parser(core, core->input.argv_struct);
        recursive_error_check(core, core->tree.root);
        if (!core->tree.parse_error)
            core->exit.last_value = execute_node(core, core->tree.root,
        STDIN_FILENO, STDOUT_FILENO);
        free_tree(core->tree.root);
    }
    free_argv_t(core->input.argv_struct);
    core->input.argv_struct = NULL;
    core->tree.root = NULL;
    return 0;
}

/*
** to skip the spaces so that i know when i should skip the line cus no command
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
** this is how we prompt the user
** if this while loop breaks the program stops
** the rushed_exit boolean is for ctrl d, which will make the program return
** the last exit value
*/
void main_loop(core_t *core)
{
    char *input = NULL;
    char *trimmed = NULL;

    while (core->com.exit == false) {
        input = get_input();
        if (input == NULL) {
            core->exit.rushed_exit = true;
            break;
        }
        trimmed = format_input(input);
        if (trimmed[0] == '\0') {
            free(input);
            continue;
        }
        handle_argv(core, input);
        update_jobs(core, false);
        free(input);
    }
    free_everything(core, input);
}
