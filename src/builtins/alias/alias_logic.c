/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** alias_logic
*/

#include "my.h"

/*
** Updates an existing alias command
** Returns 1 if alias was found and updated, 0 otherwise
*/
static int update_existing_alias(alias_t *head, const char *name,
    const char *command)
{
    alias_t *current = head;

    while (current) {
        if (my_strcmp(current->name, name) == 0) {
            free(current->command);
            current->command = my_strdup(command);
            return 1;
        }
        if (!current->next)
            break;
        current = current->next;
    }
    return 0;
}

static alias_t *find_last_node(alias_t *head)
{
    alias_t *current = head;

    if (!current)
        return NULL;
    while (current->next)
        current = current->next;
    return current;
}

static void append_new_alias(alias_t **head, alias_t *new_node)
{
    alias_t *last_node = NULL;

    if (!*head) {
        *head = new_node;
        return;
    }
    last_node = find_last_node(*head);
    last_node->next = new_node;
}

void add_alias(alias_t **head, const char *name, const char *command)
{
    alias_t *new_node = NULL;

    if (!head)
        return;
    if (update_existing_alias(*head, name, command))
        return;
    new_node = create_alias_node(name, command);
    if (!new_node)
        return;
    append_new_alias(head, new_node);
}
