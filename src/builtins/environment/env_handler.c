/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** env_handler
*/

#include "my.h"
#include "struct.h"

static bool is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

static bool is_letter(char c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        return true;
    }
    return false;
}

static bool is_underscore(char c)
{
    if (c == '_') {
        return true;
    }
    return false;
}

static bool failure_condition(const char *name, int output)
{
    int i = 0;

    while (name[i]) {
        if (!is_digit(name[i]) && !is_letter(name[i]) &&
        !is_underscore(name[i])) {
            my_putstr_fd(
            "setenv: Variable name must contain alphanumeric characters.\n",
            output);
            return true;
        }
        i++;
    }
    if (is_digit(name[0])) {
        my_putstr_fd("setenv: Variable name must begin with a letter.\n",
        output);
        return true;
    }
    return false;
}

static char *initialize_and_check_name(core_t *core, argv_t *argv_struct,
    int input, int output)
{
    int argc = argc_counter(argv_struct->argv);

    if (argc == 1) {
        print_env(core, argv_struct, input, output);
        return NULL;
    }
    if (argc > 3) {
        my_putstr_fd("setenv: Too many arguments.\n", output);
        core->exit.last_failed = true;
    }
    return argv_struct->argv[1];
}

static char *content(core_t *core, char **argv)
{
    int argc = argc_counter(argv);

    if (argc == 3) {
        return argv[2];
    }
    return NULL;
}

/*
 ** similar to modify content: if it finds the node, it updates content,
 if it can't find it, it creates a new one at the end of list
 ** if it is called on its own, it does a print_env (argc of 1)
 ** if only the name of node is inputed it will
 set the content of the node to  or just make node name if necessary
 ** quite a few rules for node name so watch out
 (returns 84 and sets the last_failed to true)
*/
int setenv_direct(core_t *core, argv_t *a_struc, int input, int output)
{
    env_t *current = core->head;
    const char *name = initialize_and_check_name(core, a_struc, input, output);
    const char *new_content = content(core, a_struc->argv);

    if (core->exit.last_failed)
        return 84;
    if (!core->head || !name || failure_condition(name, output)) {
        core->exit.last_failed = true;
        return 84;
    }
    while (current) {
        if (my_strcmp(current->name, name) == 0) {
            free(current->content);
            current->content = my_strdup(new_content);
            return 0;
        }
        current = current->next;
    }
    add_to_list(&core->head, name, new_content);
    return 84;
}

/*
 ** Not to be confused withsetenv_direct this is not meant for direct use
 but for modifying something internally.
 ** essentialy does the same thing as setenv_direct but if it fails,
 it only gives back 84
 ** it cannot run print_env
*/
int modify_content(env_t **head, const char *name, const char *new_content,
    int output)
{
    env_t *current = *head;

    if (!head || failure_condition(name, output) == true)
        return 84;
    while (current) {
        if (my_strcmp(current->name, name) == 0) {
            free(current->content);
            current->content = my_strdup(new_content);
            return 0;
        }
        current = current->next;
    }
    add_to_list(head, name, new_content);
    return 84;
}

/*
 ** prints the env list like if it was one big array
*/
int print_env(core_t *core, argv_t *argv_struct, int input_fd, int output_fd)
{
    env_t *current = core->head;

    while (current != NULL) {
        my_putstr_fd(current->name, output_fd);
        my_putstr_fd("=", output_fd);
        if (current->content)
            my_putstr_fd(current->content, output_fd);
        my_putstr_fd("\n", output_fd);
        current = current->next;
    }
    return 0;
}

void free_list(env_t *head)
{
    env_t *current = head;
    env_t *temp = NULL;

    while (current != NULL) {
        temp = current->next;
        free(current->name);
        free(current->content);
        free(current);
        current = temp;
    }
}
