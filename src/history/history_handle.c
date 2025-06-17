/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** history_handle
*/

#include "struct.h"
#include "my.h"
#include <stdio.h>
#include <unistd.h>

/*
** we go through every single index until there is no longer anything to replac
*/
void history_replace_all(core_t *core, argv_t *argv_struct)
{
    int index = 0;

    while (argv_struct->argv[index]) {
        if (is_history_str(argv_struct->argv[index])) {
            history_replace(core, argv_struct, index);
            index--;
        }
        index++;
    }
    if (argv_struct->argv && argc_counter(argv_struct->argv) != 0 &&
    isatty(STDIN_FILENO)) {
        add_to_hist_list(&core->history.hist_head, &core->history.last,
        argv_struct->argv, core->history.file_dp);
        print_array(argv_struct->argv);
        fflush(stdout);
        my_cooler_putstr("\n");
        fflush(stdout);
    }
}

/*
** this is where we call and organise all the funcs that we use
** this func is called before parsing to a tree, after
changing the tree to smth recognisable
*/
void history_handle(core_t *core, argv_t *argv_struct)
{
    if (!contains_history_command(core, argv_struct) && isatty(STDIN_FILENO)) {
        add_to_hist_list(&core->history.hist_head, &core->history.last,
        argv_struct->argv, core->history.file_dp);
        return;
    }
    history_replace_all(core, argv_struct);
}
