/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** alias_handler
*/

#include "my.h"
#include "struct.h"

static int print_aliases(core_t *core, int output_fd)
{
    alias_t *current = core->alias_head;

    while (current) {
        my_putstr_fd(current->name, output_fd);
        my_putstr_fd("\t", output_fd);
        my_putstr_fd(current->command, output_fd);
        my_putstr_fd("\n", output_fd);
        current = current->next;
    }
    return 0;
}

static int print_one_alias(core_t *core, const char *name, int output_fd)
{
    char *command = find_alias(core->alias_head, name);

    if (!command) {
        my_putstr_fd(name, output_fd);
        my_putstr_fd(": Undefined alias.\n", output_fd);
        return 84;
    }
    my_putstr_fd(name, output_fd);
    my_putstr_fd("\t", output_fd);
    my_putstr_fd(command, output_fd);
    my_putstr_fd("\n", output_fd);
    return 0;
}

static int calc_concat_length(char **argv, int start, int end)
{
    int total_len = 0;
    int i = 0;

    for (i = start; i < end; i++) {
        total_len += my_strlen(argv[i]);
        if (i < end - 1)
            total_len++;
    }
    return total_len;
}

static void copy_args_to_string(char *result, char **argv, int start, int end)
{
    int current_pos = 0;
    int i = 0;

    for (i = start; i < end; i++) {
        my_strcpy(result + current_pos, argv[i]);
        current_pos += my_strlen(argv[i]);
        if (i < end - 1) {
            result[current_pos] = ' ';
            current_pos++;
        }
    }
    result[current_pos] = '\0';
}

static char *concat_arguments(char **argv, int start, int end)
{
    char *result = NULL;
    int total_len = 0;

    total_len = calc_concat_length(argv, start, end);
    result = malloc(total_len + 1);
    if (!result)
        return NULL;
    copy_args_to_string(result, argv, start, end);
    return result;
}

int alias_handler(
    core_t *core, argv_t *argv_struct, int input_fd, int output_fd)
{
    int argc = argc_counter(argv_struct->argv);
    char *command = NULL;

    if (argc == 1)
        return print_aliases(core, output_fd);
    if (argc == 2)
        return print_one_alias(core, argv_struct->argv[1], output_fd);
    command = concat_arguments(argv_struct->argv, 2, argc);
    if (!command)
        return 84;
    add_alias(&core->alias_head, argv_struct->argv[1], command);
    free(command);
    return 0;
}

int unalias_handler(
    core_t *core, argv_t *argv_struct, int input_fd, int output_fd)
{
    int argc = argc_counter(argv_struct->argv);
    int ret = 0;

    if (argc < 2) {
        my_putstr_fd("unalias: Too few arguments.\n", output_fd);
        return 84;
    }
    for (int i = 1; i < argc; i++) {
        if (delete_alias(&core->alias_head, argv_struct->argv[i]) != 0) {
            my_putstr_fd(argv_struct->argv[i], output_fd);
            my_putstr_fd(": Undefined alias.\n", output_fd);
            ret = 84;
        }
    }
    return ret;
}
