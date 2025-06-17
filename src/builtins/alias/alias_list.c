/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** alias_list
*/

#include "my.h"
#include "struct.h"

alias_t *create_alias_node(const char *name, const char *command)
{
    alias_t *new_node = malloc(sizeof(alias_t));

    if (!new_node) {
        return NULL;
    }
    new_node->name = my_strdup(name);
    new_node->command = my_strdup(command);
    new_node->next = NULL;
    return new_node;
}

char *find_alias(alias_t *head, const char *name)
{
    alias_t *current = head;

    while (current) {
        if (my_strcmp(current->name, name) == 0) {
            return current->command;
        }
        current = current->next;
    }
    return NULL;
}

static void free_alias_node(alias_t *node)
{
    if (!node){
        return;
    }
    free(node->name);
    free(node->command);
    free(node);
}

static int delete_head_alias(alias_t **head, const char *name)
{
    alias_t *current = *head;

    if (my_strcmp(current->name, name) == 0) {
        *head = current->next;
        free_alias_node(current);
        return 0;
    }
    return 84;
}

static int delete_inner_alias(alias_t *head, const char *name)
{
    alias_t *current = head;
    alias_t *prev = NULL;

    while (current && my_strcmp(current->name, name) != 0) {
        prev = current;
        current = current->next;
    }
    if (!current) {
        return 84;
    }
    prev->next = current->next;
    free_alias_node(current);
    return 0;
}

int delete_alias(alias_t **head, const char *name)
{
    if (!head || !*head) {
        return 84;
    }
    if (delete_head_alias(head, name) == 0){
        return 0;
    }
    return delete_inner_alias(*head, name);
}

void free_alias_list(alias_t *head)
{
    alias_t *current = head;
    alias_t *next = NULL;

    while (current) {
        next = current->next;
        free(current->name);
        free(current->command);
        free(current);
        current = next;
    }
}
