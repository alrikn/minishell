/*
** EPITECH PROJECT, 2024
** CPOOL DAY04 task01
** File description:
** task01
*/

#include <stdio.h>
#include <unistd.h>

void recursive_iteration(long a)
{
    long count;

    if (a >= 10) {
        recursive_iteration(a / 10);
        a = (a % 10);
    }
    count = (a + 48);
    write(1, &count, 1);
}

long my_put_nbr(long nb)
{
    recursive_iteration(nb);
    return 0;
}
