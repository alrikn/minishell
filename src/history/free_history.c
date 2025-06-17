/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** free_history
*/

#include "my.h"
#include "struct.h"

void free_history(hist_list_t *hist_head)
{
    hist_list_t *temp = hist_head;
    hist_list_t *current = hist_head;

    while (current) {
        temp = current;
        current = current->next;
        free(temp->name);
        free(temp->content);
        free(temp);
        temp = NULL;
    }
}
