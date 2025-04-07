/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** operators
*/

#include "struct.h"

const operator_t MY_OPERATORS[] = {
    {OP_SEMICOLON, ";"},
    {OP_AND, "&&"},
    {OP_OR, "||"},
    {OP_LSHIFT, "<"},
    {OP_LAPPEND, "<<"},
    {OP_RSHIFT, ">"},
    {OP_RAPPEND, ">>"},
    {OP_PIPE, "|"},
    {OP_NONE, NULL}
};
