/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** just a place to hold structs so that my.h is'nt bloated
*/

#ifndef STRUCT_H
    #define STRUCT_H
    #include <stdbool.h>
    #include <time.h>

typedef enum {
    OP_SEMICOLON,
    OP_AND,
    OP_OR,
    OP_LSHIFT,
    OP_LAPPEND,
    OP_RSHIFT,
    OP_RAPPEND,
    OP_PIPE,
    OP_NONE
} operator_list_t;

typedef struct {
    operator_list_t type;
    const char *symbol;
} operator_t;

extern const operator_t MY_OPERATORS[];

typedef struct env_list {
    char *name;
    char *content;
    struct env_list *next;
} env_t;

/*
if one of the flags has been called upon,
then flag will be true otherwise it is false
*/
typedef struct commands {
    bool exit : 1;
    bool flag : 1;
} com_t;

typedef struct new_input {
    char **argv;
    int argc;
    char **env;
} input_t;

typedef struct exit_status {
    int last_value;
    bool rushed_exit;
    bool last_failed;
} status_t;

typedef struct sub_input {
    char **argv;
    char **env;
    char *path;
    char **command;
} sub_input_t;

/*
 ** the typed defines the children
*/
typedef struct tree {
    char **argv;
    int argc;
    operator_list_t type;
    bool done;
    bool is_leaf;
    struct tree *right;
    struct tree *left;
} tree_t;

typedef struct argv_commands {
    tree_t *root;
} tree_com_t;

typedef struct core {
    com_t com;
    input_t input;
    sub_input_t sub_input;
    env_t *head;
    status_t exit;
    tree_com_t tree;
} core_t;

#endif
