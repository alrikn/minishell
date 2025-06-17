/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** history
*/

#include "my.h"
#include "struct.h"

/*
** this just prints history nothing else
*/
int history_print(core_t *core, argv_t *argv_struct, int in, int out)
{
    hist_list_t *current = core->history.hist_head;
    long num = 1;

    while (current) {
        printf("%ld\t%s\n", num, current->content);
        num++;
        current = current->next;
    }
    return 0;
}
