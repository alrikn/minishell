/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** operators
*/

#include "struct.h"

/*
** handles hiearchy of execution
*/
const operator_t MY_OPERAT[] = {
    {OP_SEMICOLON, ";"},
    {OP_AND, "&&"},
    {OP_OR, "||"},
    {OP_LSHIFT, "<"},
    {OP_LAPPEND, "<<"},
    {OP_RSHIFT, ">"},
    {OP_RAPPEND, ">>"},
    {OP_PIPE, "|"},
    {OP_BG_S, "&"},
    {OP_NONE, NULL}
};

/*
** for debugging purposes
*/
const operator_t OPERATOR_PRINT[] = {
    {OP_SEMICOLON, ";"},
    {OP_PAREN, "()"},
    {OP_AND, "&&"},
    {OP_OR, "||"},
    {OP_LSHIFT, "<"},
    {OP_LAPPEND, "<<"},
    {OP_RSHIFT, ">"},
    {OP_RAPPEND, ">>"},
    {OP_PIPE, "|"},
    {OP_NONE, NULL}
};
