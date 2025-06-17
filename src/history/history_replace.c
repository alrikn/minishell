/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** history_replace
*/

#include "my.h"
#include "struct.h"
#include <string.h>

/*
** the result is a new malloc
*/
char *find_hist_content(char *name, hist_list_t *last)
{
    hist_list_t *temp = last;

    if (!name || name[0] == '\0')
        return NULL;
    while (temp) {
        if (my_strcmp(name, temp->name) == 0)
            return my_strdup(temp->content);
        temp = temp->prev;
    }
    return NULL;
}

static int index_handle(argv_t *new_argv_struct, int i,
    char **re_argv, type_list_t *re_types)
{
    int absolute_index = 0;

    for (int new_index = 0; new_argv_struct->argv[new_index]; new_index++) {
        re_argv[i + new_index] = new_argv_struct->argv[new_index];
        re_types[i + new_index] = new_argv_struct->types[new_index];
        absolute_index = i + new_index;
    }
    return absolute_index;
}

static argv_t *reassign_handle(char **re_argv, type_list_t *re_types,
    argv_t *old_argv_struct, int len)
{
    re_argv[len - 1] = NULL;
    re_types[len - 1] = NONE;
    free(old_argv_struct->argv);
    free(old_argv_struct->types);
    old_argv_struct->types = re_types;
    old_argv_struct->argv = re_argv;
    return old_argv_struct;
}

/*
** everything that is under the index we have to change
**(so everything we dont have to change and that can stay the same)
*/
static void realloc_baseline(char **re_argv, type_list_t *re_types, int i,
    argv_t *old_argv_struct)
{
    re_argv[i] = old_argv_struct->argv[i];
    re_types[i] = old_argv_struct->types[i];
}

static argv_t *argv_editor(argv_t *old_argv_struct, argv_t *new_argv_stru,
    int index)
{
    int old_len = argc_counter(old_argv_struct->argv);
    int malloc_len = old_len + argc_counter(new_argv_stru->argv);
    char **re_argv = malloc(sizeof(char *) * malloc_len + 1);
    type_list_t *re_types = malloc(sizeof(type_list_t) * malloc_len + 1);
    int absolute_index = 0;

    for (int i = 0; i < old_len; i++) {
        if (i < index)
            realloc_baseline(re_argv, re_types, i, old_argv_struct);
        if (i > index) {
            realloc_baseline(re_argv, re_types, i, old_argv_struct);
        }
        if (i == index) {
            free(old_argv_struct->argv[i]);
            absolute_index = index_handle(new_argv_stru, i, re_argv, re_types);
        }
        absolute_index++;
    }
    return reassign_handle(re_argv, re_types, old_argv_struct, malloc_len);
}

static void bad_hist_index(argv_t *argv_struct, int *i, int index, int *abs_i)
{
    if (*i == index) {
        free(argv_struct->argv[index]);
        *abs_i = *i;
    }
}

/*
** if bad hist call (as in couldnt find command in history)
** we delete the the offending memory call nd repalce it with null
** (the offending memory call is the bad memory argv index)
*/
argv_t *bad_hist_call(argv_t *old_argv_struct, int index)
{
    int new_len = argc_counter(old_argv_struct->argv);
    char **re_argv = NULL;
    type_list_t *re_types = NULL;
    int absolute_index = 0;

    if (new_len <= 0)
        return old_argv_struct;
    re_types = malloc(sizeof(type_list_t) * (new_len));
    re_argv = malloc(sizeof(char *) * (new_len));
    for (int i = 0; i <= new_len; i++) {
        if (i < index)
            realloc_baseline(re_argv, re_types, i, old_argv_struct);
        if (i > index) {
            re_argv[absolute_index] = old_argv_struct->argv[i];
            re_types[absolute_index] = old_argv_struct->types[i];
            absolute_index++;
        }
        bad_hist_index(old_argv_struct, &i, index, &absolute_index);
    }
    return reassign_handle(re_argv, re_types, old_argv_struct, new_len);
}

/*
** the index is which argv we wanna replace
** it has to start with !
*/
argv_t *history_replace(core_t *core, argv_t *old_argv_struct, int index)
{
    argv_t *new_argv_struct = NULL;
    char *hist_content = find_hist_content(old_argv_struct->argv[index] + 1,
    core->history.last);

    if (!hist_content) {
        if (my_strlen(old_argv_struct->argv[index] + 1) > 0)
            printf("%s: Event not found.\n", old_argv_struct->argv[index] + 1);
        else
            printf("!: Event not found.\n");
        core->exit.last_failed = true;
        return bad_hist_call(old_argv_struct, index);
    }
    new_argv_struct = input_line_parser(hist_content);
    old_argv_struct = argv_editor(old_argv_struct, new_argv_struct, index);
    free(hist_content);
    free(new_argv_struct->argv);
    free(new_argv_struct->types);
    free(new_argv_struct);
    return old_argv_struct;
}
