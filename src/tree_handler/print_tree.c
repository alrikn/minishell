/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** print_tree
*/

#include "my.h"
#include "struct.h"
#include <stdio.h>

static void print_type(tree_t *node)
{
    int i = 0;

    while (OPERATOR_PRINT[i].symbol && node->type != OPERATOR_PRINT[i].type)
        i++;
    if (OPERATOR_PRINT[i].symbol) {
        my_cooler_putstr(" node type is ");
        my_cooler_putstr(OPERATOR_PRINT[i].symbol);
        my_cooler_putstr("\n");
        fflush(stdout);
    }
}

int recursive_print(tree_t *node)
{
    tree_t *next;

    if (!node)
        return 84;
    print_type(node);
    if (node->argv_struct && node->argv_struct->argv) {
        print_array(node->argv_struct->argv);
        my_cooler_putstr("\n");
    }
    if (node->left) {
        next = node->left;
        my_cooler_putstr("left: ");
        recursive_print(next);
    }
    if (node->right) {
        next = node->right;
        my_cooler_putstr("right: ");
        recursive_print(next);
    }
    return 0;
}

/*
 ** prints the tree order
*/
int print_tree(tree_t *root)
{
    tree_t *temp = root;

    my_cooler_putstr("start print tree\n");
    if (recursive_print(temp) == 84) {
        my_cooler_putstr("smth_went_wrong in the print tree\n");
        return 84;
    }
    my_cooler_putstr("\n");
    my_cooler_putstr("end print tree\n");
    return 0;
}
