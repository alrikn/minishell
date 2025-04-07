/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** env_list
*/

#include "struct.h"
#include "my.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static env_t *create_node(const char *name, const char *content)
{
    env_t *new_node = malloc(sizeof(env_t));

    if (new_node == NULL) {
        return NULL;
    }
    new_node->name = my_strdup(name);
    new_node->content = my_strdup(content);
    new_node->next = NULL;
    return new_node;
}

/*
 ** adds a node a end of list (did i really have to explain that?)
*/
void add_to_list(env_t **head, const char *name, const char *content)
{
    env_t *new_node = create_node(name, content);
    env_t *temp = new_node;

    if (!new_node) {
        return;
    }
    if (*head == NULL) {
        *head = new_node;
    } else {
        temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

static void delete_helper(env_t *current)
{
    free(current->content);
    free(current->name);
    free(current);
}

int delete_node(env_t **head, const char *name)
{
    env_t *current = *head;
    env_t *old = NULL;

    if (!head)
        return 84;
    if (my_strcmp(current->name, name) == 0) {
        *head = current->next;
        delete_helper(current);
        return 0;
    }
    while (current) {
        if (my_strcmp(current->name, name) == 0) {
            old->next = current->next;
            delete_helper(current);
            return 0;
        }
        old = current;
        current = current->next;
    }
    return 84;
}

/*
 ** this does the exact same thing as delete_node except
 it only takes the core struct as input
*/
int unsetenv_direct(core_t *core, char **argv)
{
    env_t *current = core->head;
    env_t *old = NULL;

    if (!core->head)
        return 84;
    if (my_strcmp(current->name, argv[1]) == 0) {
        core->head = current->next;
        delete_helper(current);
        return 0;
    }
    while (current) {
        if (my_strcmp(current->name, argv[1]) == 0) {
            old->next = current->next;
            delete_helper(current);
            return 0;
        }
        old = current;
        current = current->next;
    }
    return 84;
}

/*
 ** this function DOES NOT strdup its responses
 ** it gives you the content str directly from the node meaning that
 if you mess with it, you mess with the linked list DIRECTLY
*/
char *find_content(env_t *head, const char *name)
{
    env_t *current = head;

    while (current != NULL) {
        if (my_strcmp(current->name, name) == 0) {
            return current->content;
        }
        current = current->next;
    }
    return NULL;
}

/*
 ** This function is called only once to make the env
 for the first time that we take from the main
*/
env_t *parse_env(char **env)
{
    env_t *head = NULL;
    char *env_copy = NULL;
    char *name = NULL;
    char *content = NULL;

    for (int i = 0; env[i]; i++) {
        env_copy = my_strdup(env[i]);
        if (!env_copy) {
            free_list(head);
            return NULL;
        }
        name = strtok(env_copy, "=");
        content = strtok(NULL, "\0");
        add_to_list(&head, name, content);
        free(env_copy);
    }
    return head;
}
