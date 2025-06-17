/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** lvl_update
*/

#include "my.h"

/*
** lvl = ((char **)NULL)[0];
*/
void update_shlvl(core_t *core)
{
    char *old_shlvl = find_content(core->head, "SHLVL");
    int shlvl = my_str_to_int(old_shlvl) + 1;
    char *lvl = my_int_to_str(shlvl);

    modify_content(&core->head, "SHLVL", lvl, 1);
    free(lvl);
}
