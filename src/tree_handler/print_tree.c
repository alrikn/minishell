/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** print_tree
*/

#include "my.h"
#include "struct.h"

static void print_type(tree_t *node)
{
    int i = 0;

    while (MY_OPERATORS[i].symbol && node->type != MY_OPERATORS[i].type)
        i++;
    if (MY_OPERATORS[i].symbol) {
        my_cooler_putstr(" node type is ");
        my_cooler_putstr(MY_OPERATORS[i].symbol);
        my_cooler_putstr("\n");
    }
}

int recursive_print(tree_t *node)
{
    tree_t *next;

    if (!node)
        return 84;
    print_type(node);
    if (node->argv)
        print_array(node->argv);
    if (node->left) {
        next = node->left;
        recursive_print(next);
    }
    if (node->right) {
        next = node->right;
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
