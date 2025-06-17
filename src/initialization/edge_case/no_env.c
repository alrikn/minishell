/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** no_env
*/

#include "my.h"

/*
** this function gets activated when the shell is
called with a lack of environnemnt
*/
void no_environment(core_t *core)
{
    char hostname[HOST_NAME_MAX + 2];
    char buffer[1025];
    char *second_buffer = getcwd(buffer, sizeof(buffer));

    gethostname(hostname, HOST_NAME_MAX + 1);
    add_to_list(&core->head, "SHLVL", "1");
    add_to_list(&core->head, "LOGNAME", getlogin());
    add_to_list(&core->head, "HOST", hostname);
    add_to_list(&core->head, "PWD", second_buffer);
}
