/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** list_to_array
*/

#include "my.h"
#include "struct.h"
#include <stdlib.h>
#include <string.h>

static int counter(env_t *head)
{
    int count = 0;
    env_t *current = head;

    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

char **list_to_array(env_t *head)
{
    char **array = NULL;
    env_t *current = head;
    int i = 0;
    int len = 0;

    array = malloc(sizeof(char *) * (counter(head) + 1));
    if (!array)
        return NULL;
    while (current) {
        len = my_strlen(current->name) + 1 + my_strlen(current->content) + 1;
        array[i] = malloc(len);
        my_strcpy(array[i], current->name);
        my_strcat(array[i], "=");
        my_strcat(array[i], current->content);
        current = current->next;
        i++;
    }
    array[i] = NULL;
    return array;
}
