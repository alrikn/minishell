/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** just a place to hold structs so that my.h is'nt bloated
*/

#ifndef STRUCT_H
    #define STRUCT_H
    #include <ncurses.h>
    #include <stdbool.h>
    #include <time.h>
    #include <stdio.h>

/*
** NONE woul kind of be like the null (signifies end of list)
** Error is for when there is not correct amount of things. ex:
$> echo 'ls
*/
typedef enum type_list {
    NORM,
    SING_QUOTE,
    DOUBL_QUOTE,
    BACKTICK,
    NONE,
    ERROR,
} type_list_t;

typedef struct {
    type_list_t type;
    const char letter;
} inhibitor_t;

extern const inhibitor_t MY_INHIBITORS[];

/*
** this to keep track of what to ignore and what not to
*/
typedef struct argv {
    char **argv;
    type_list_t *types;
} argv_t;

typedef enum {
    OP_SEMICOLON,
    OP_AND,
    OP_OR,
    OP_LSHIFT,
    OP_LAPPEND,
    OP_RSHIFT,
    OP_RAPPEND,
    OP_PIPE,
    OP_BG_S,
    OP_PAREN, // ()
    OP_NONE
} operator_list_t;

typedef struct {
    operator_list_t type;
    const char *symbol;
} operator_t;

extern const operator_t MY_OPERAT[];

extern const operator_t OPERATOR_PRINT[];

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
    bool exit;
    bool flag;
    int exit_value;
} com_t;

typedef struct new_input {
    argv_t *argv_struct;
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

typedef struct alias_list alias_t;

typedef struct alias_list {
    char *name;
    char *command;
    alias_t *next;
} alias_t;

/*
 ** the typed defines the children
*/
typedef struct tree {
    argv_t *argv_struct;
    int argc;
    operator_list_t type;
    bool error_occured;
    bool done;
    bool is_leaf;
    struct tree *right;
    struct tree *left;
} tree_t;

typedef struct tree_struct {
    tree_t *root;
    bool parse_error;
} tree_com_t;

/*
** this is the history list
*/
typedef struct history_list {
    char *name;
    char *content;
    struct history_list *next;
    struct history_list *prev;
} hist_list_t;

typedef struct history_struct {
    hist_list_t *hist_head;
    hist_list_t *last;
    FILE *file_dp;
} hist_struct_t;

typedef enum {
    J_FIRST,
    J_SECOND,
    J_NONE
} job_priority_t;

typedef struct job_list {
    char *command;
    int job_nbr;
    pid_t current_job;
    int prev_signal;
    bool just_added;
    job_priority_t job_priority;
    struct job_list *next;
    struct job_list *prev;
} job_list_t;

typedef struct job_control {
    job_list_t *job_head;
    bool is_background;
    bool called_jobs;
    int shell_pgid;
} control_t;

typedef struct core {
    com_t com;
    input_t input;
    sub_input_t sub_input;
    env_t *head;
    alias_t *alias_head;
    status_t exit;
    tree_com_t tree;
    hist_struct_t history;
    control_t job;
} core_t;

typedef enum builtins {
    BN_ENV,
    BN_CD,
    BN_SETENV,
    BN_UNSETENV,
    BN_ECHO,
    BN_EXIT,
    BN_FG,
    BN_BG,
    BN_JOBS,
    BN_ALIAS,
    BN_UNALIAS,
    BN_HISTORY,
    BUILTIN_MAX
} builtins_t;

typedef int (*builtin_fn_t)(core_t *, argv_t *argv_stru, int in, int out);

typedef struct builtin_tuple {
    char *bn_name;
    builtin_fn_t bn_function;
} builtin_tuple_t;

#endif
