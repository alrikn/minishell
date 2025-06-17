/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parenthese_parser
*/

#include "my.h"
#include "struct.h"

static bool error_message_parent(int entrenchment, tree_t *node)
{
    if (entrenchment != 0)
        node->error_occured = true;
    if (entrenchment > 0)
        my_cooler_putstr("Too many )'s.\n");
    if (entrenchment < 0)
        my_cooler_putstr("Too many ('s.\n");
    if (entrenchment < 0 || entrenchment > 0)
        return true;
    return false;
}

static int entrenchment_finder(char **argv, int *last_pos,
    int *entrenchment, int *skip_spot)
{
    int i = 0;

    do {
        i++;
        if (my_strcmp("(", argv[*last_pos]) == 0) {
            *entrenchment -= 1;
            *skip_spot = *last_pos - 1;
        }
        if (my_strcmp(")", argv[*last_pos]) == 0) {
            *entrenchment += 1;
        }
        *last_pos -= 1;
    } while (*last_pos >= 0 && argv[*last_pos] && *entrenchment != 0);
    return i;
}

static bool empty_parentheses_check(tree_t *node, int entrenchment)
{
    if (entrenchment == 0)
        my_cooler_putstr("Invalid null command.\n");
    node->error_occured = true;
    return false;
}

/*
** we assume we are currently on a )
**returns true if there is nothing to skip
(as in we have to deal with interior now)
**or false if there is stuff outside of it (we forget about it)
**last argv is to check that we start at last pos
** first argv we end at first pos
*/
bool skip_parenthese(tree_t *node, char **argv, int *last_pos)
{
    int entrenchment = 0;
    int original_pos = *last_pos;
    int skip_spot = *last_pos;
    bool last_argv = ((argc_counter(argv) - 1) == *last_pos) ? true : false;

    if (entrenchment_finder(argv, last_pos, &entrenchment, &skip_spot) == 2)
        return empty_parentheses_check(node, entrenchment);
    error_message_parent(entrenchment, node);
    if (node->error_occured == true)
        return false;
    if (my_strcmp("(", argv[*last_pos + 1]) == 0 &&
    last_argv && *last_pos < 0) {
        *last_pos = original_pos;
        return true;
    } else {
        *last_pos = skip_spot;
        return false;
    }
}

/*
** argc -1 cus null pointer don't count
** node left cus left is best
*/
tree_t *deal_with_paren(tree_t *node, argv_t *argv_struc, int last_pos)
{
    int argc = argc_counter(argv_struc->argv);
    argv_t *new_struct = NULL;

    if (argc == 2) {
        node->error_occured = true;
        return node;
    }
    new_struct = malloc(sizeof(argv_t));
    new_struct->types = malloc(sizeof(type_list_t) * (argc - 1));
    new_struct->argv = malloc(sizeof(char *) * (argc - 1));
    for (int i = 1; argv_struc->argv[i - 1] && i < argc - 1; i++) {
        new_struct->argv[i - 1] = my_strdup(argv_struc->argv[i]);
        new_struct->types[i - 1] = argv_struc->types[i];
    }
    new_struct->argv[argc - 2] = NULL;
    new_struct->types[argc - 2] = NONE;
    node->type = OP_PAREN;
    node->left = recursive_parse(new_struct);
    free_argv_t(new_struct);
    return node;
}

/*
** returns true if there is an error (also handles the error printing)
*/
bool entrenchment_error_finder(core_t *core, char **argv)
{
    int entrenchment = 0;
    int i = 0;

    while (argv[i]) {
        if (my_strcmp("(", argv[i]) == 0)
            entrenchment -= 1;
        if (my_strcmp(")", argv[i]) == 0)
            entrenchment += 1;
        i++;
    }
    if (entrenchment != 0) {
        core->tree.parse_error = true;
        if (entrenchment > 0)
            my_cooler_putstr("Too many )'s.\n");
        if (entrenchment < 0)
            my_cooler_putstr("Too many ('s.\n");
        return true;
    }
    return false;
}
