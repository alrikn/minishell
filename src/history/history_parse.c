/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** history_write
*/

#include "my.h"
#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *open_file(core_t *core)
{
    char *path = find_content(core->head, "HOME");
    int len = my_strlen(path);
    char *full_path = NULL;
    FILE *reading_path = NULL;

    if (!path)
        return NULL;
    if (len <= 0)
        return NULL;
    full_path = malloc(sizeof(char) * (len + my_strlen("/.42sh_hist") + 1));
    if (!full_path)
        return NULL;
    strcpy(full_path, path);
    strcat(full_path, "/.42sh_hist");
    core->history.file_dp = fopen(full_path, "a");
    reading_path = fopen(full_path, "r");
    free(full_path);
    return reading_path;
}

/*
** this should be called as early as possible
** the filed is not open yet
*/
void history_parse(core_t *core)
{
    FILE *read_file = open_file(core);
    char *line = NULL;
    size_t n = 0;
    long read;
    char *copy = NULL;

    if (!read_file) {
        core->history.file_dp = fopen(".42sh_hist", "a");
        return;
    }
    read = getline(&line, &n, read_file);
    while (read > 0) {
        copy = my_strdup(line);
        parse_add_hist_list(copy, &core->history.hist_head,
        &core->history.last);
        free(copy);
        read = getline(&line, &n, read_file);
    }
    free(line);
    fclose(read_file);
}
