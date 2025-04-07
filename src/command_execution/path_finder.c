/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** path_finder
*/

#include "my.h"
#include "struct.h"
#include <stdio.h>
#include <string.h>

char **get_list_of_paths(core_t *core)
{
    char *paths = my_strdup(find_content(core->head, "PATH"));
    char **list_path = my_str_to_word_array_specific(paths, ':');

    free(paths);
    return list_path;
}

static char *direct_path(char *binary_name)
{
    if (access(binary_name, F_OK) == 0) {
        return my_strdup(binary_name);
    }
    return NULL;
}

/*
 ** once we've found where in the path it is, we build the full path
*/
static char *path_loop(char *full_path, char *b_name, char **list_path, int i)
{
    full_path = malloc(my_strlen(list_path[i]) + 1 +
    my_strlen(b_name) + 1);
    if (!full_path)
        return NULL;
    my_strcpy(full_path, list_path[i]);
    my_strcat(full_path, "/");
    my_strcat(full_path, b_name);
    if (access(full_path, F_OK) == 0) {
        free_array(list_path);
        return full_path;
    }
    free(full_path);
    full_path = NULL;
    return NULL;
}

/*
 ** this function will return the path by searching through
 current directory and the env PATH
 **if ther is '/' i assume you know what you are doing
 and don't touch the env path
*/
char *find_path(char **argv, core_t *core)
{
    char **list_path = NULL;
    char *binary_name = argv[0];
    char *full_path = NULL;

    if (first_char(binary_name, '/'))
        return direct_path(binary_name);
    list_path = get_list_of_paths(core);
    if (!list_path) {
        free_array(list_path);
        return NULL;
    }
    for (int i = 0; list_path[i]; i++) {
        full_path = path_loop(full_path, binary_name, list_path, i);
        if (full_path != NULL)
            return full_path;
    }
    free_array(list_path);
    return NULL;
}
