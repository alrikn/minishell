/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** history_memory
*/

#include "my.h"
#include "struct.h"
#include <stdio.h>
#include <string.h>

static hist_list_t *create_node(char **argv_str, FILE *file)
{
    hist_list_t *new_node = malloc(sizeof(hist_list_t));
    char *skip = "\n";

    if (new_node == NULL) {
        return NULL;
    }
    new_node->name = my_strdup(argv_str[0]);
    new_node->content = array_to_str(argv_str);
    new_node->next = NULL;
    new_node->prev = NULL;
    fwrite(new_node->content, sizeof(char),
    my_strlen(new_node->content), file);
    fwrite(skip, 1, 1, file);
    return new_node;
}

static char *remove_line(char *str)
{
    int i = 0;

    while (str[i]) {
        if (str[i] == '\n') {
            str[i] = '\0';
            return str;
        }
        i++;
    }
    return str;
}

static hist_list_t *create_parse_node(char *str)
{
    char *copy = my_strdup(str);
    char *name = NULL;
    hist_list_t *new_node = NULL;

    if (!copy)
        return NULL;
    name = strtok(copy, " \n");
    if (!name) {
        free(copy);
        return NULL;
    }
    new_node = malloc(sizeof(hist_list_t));
    new_node->name = my_strdup(name);
    str = remove_line(str);
    new_node->content = my_strdup(str);
    new_node->prev = NULL;
    new_node->next = NULL;
    free(copy);
    return new_node;
}

void parse_add_hist_list(char *str, hist_list_t **head, hist_list_t **last)
{
    hist_list_t *new_node = create_parse_node(str);
    hist_list_t *temp = new_node;

    if (!new_node)
        return;
    if (*head == NULL) {
        *head = new_node;
        *last = new_node;
    } else {
        temp = *last;
        temp->next = new_node;
        new_node->prev = temp;
        *last = new_node;
    }
}

/*
** this can only be called after you have replaced all
existing history calls inside the char *
** this function is not for initializing the history
list but rather user update
*/
void add_to_hist_list(hist_list_t **head, hist_list_t **last,
    char **argv, FILE *file)
{
    hist_list_t *new_node = create_node(argv, file);
    hist_list_t *temp = new_node;

    if (!new_node) {
        return;
    }
    if (*head == NULL) {
        *head = new_node;
        *last = new_node;
    } else {
        temp = *last;
        temp->next = new_node;
        new_node->prev = temp;
        *last = new_node;
    }
}
