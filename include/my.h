/*
** EPITECH PROJECT, 2024
** fake_my_hunter
** File description:
** my
*/

#ifndef INCLUDED_MY_H
    #define INCLUDED_MY_H

    #include <dirent.h>
    #include <fcntl.h>
    #include <ncurses.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <time.h>
    #include <unistd.h>
    #include "struct.h"
    #define READ  0
    #include <sys/stat.h>
    #include <ncurses.h>
    #define READ 0
    #define WRITE 1
    #define DEL 127
    #define ESC 27
    #define ETX 3
    #define EOT 4
    #define UP_ARROW 65
    #define DOWN_ARROW 66
    #define RIGHT_ARROW 67
    #define LEFT_ARROW 68

//library funcs

char *num_to_str(int num);
int num_len(int nb);
char *my_revstr(char *str);
int my_cooler_putstr(char const *str);
char *my_strcat(char *dest, char const *str);
char *my_strcpy(char *dest, char const *src);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strncpy(char *dest, char const *src, int n);
char *my_move_to_char(const char *str, int c);
char *my_strncpy(char *dest, char const *src, int n);
int my_strlen(char const *str);
int my_str_to_int(const char *str);
int my_strcmp(const char *str1, const char *str2);
char *my_strdup(char const *src);
char *my_get_time(void);
double my_str_to_float(const char *str, char **endptr);
char *my_strtok(char *str, const char *delim);
char *my_int_to_str(long int num);
int ascci_to_sum(const char *str);
char **my_str_to_word_array(char const *str);
char *last_char(const char *str, char character);
long my_put_nbr(long nb);
int my_putstr_fd(char const *str, int output_fd);
int argc_counter(char **array);
int print_array(char **array);
bool my_is_num(const char *str);
int free_array(char **array);
env_t *parse_env(char **env);
int modify_content(
    env_t **head, const char *name, const char *new_content, int output);
void add_to_list(env_t **head, const char *name, const char *content);
void free_list(env_t *head);
char *array_to_str(char **array);

/* project funcs*/

//builtins
int check_system_commands(core_t *core, argv_t *argv_struct, int in, int out);
int print_env(core_t *core, argv_t *argv_struct, int input_fd, int output_fd);
int cd_handler(core_t *core, argv_t *argv_struct, int input_fd, int output_fd);
int setenv_direct(core_t *core, argv_t *argv_struct, int input, int output);
int unsetenv_direct(core_t *core, argv_t *argv_struct, int input, int output);
int echo_handler(core_t *core, argv_t *argv_struct, int input, int output);
int exit_builtin(core_t *core, argv_t *argv_struct, int input, int output);
int history_print(core_t *core, argv_t *argv_struct, int in, int out);

//leaf execution funcs
int leaf_executor(core_t *core, int pipe_to_child, int pipe_from_child);
char *find_path(char **argv, core_t *core);

//tree execution funcs
int leaf_handler(core_t *core, argv_t *argv_struct, int input, int output);
int handle_redirection(core_t *core, tree_t *node, int in_fd, int out_fd);
int handle_parenthese(core_t *core, tree_t *node, int input_fd, int output_fd);
int handle_pipe(core_t *core, tree_t *node, int input_fd, int output_fd);
int handle_or_and(core_t *core, tree_t *node,
    int input_fd, int output_fd);
int right_shift(core_t *core, tree_t *node, int input, int output);
int right_append(core_t *core, tree_t *node, int input, int output);
int left_shift(core_t *core, tree_t *node, int input, int output);
int left_append(core_t *core, tree_t *node, int input, int output);
int execute_node(core_t *core, tree_t *node, int input_fd, int output_fd);
int back_handle(core_t *core, tree_t *node, int in, int out);

// environement funcs
char *find_content(env_t *head, const char *name);
void free_list(env_t *head);
char **list_to_array(env_t *head);
int modify_content(env_t **head, const char *name, const char *new_content,
    int output);
void add_to_list(env_t **head, const char *name, const char *content);
int delete_node(env_t **head, const char *name);
env_t *parse_env(char **env);

//testing funcs
int print_tree(tree_t *root);

// parsing funcs
char *inhibitor_parse(type_list_t type, const char *str, int *index, int *len);
tree_t *deal_with_paren(tree_t *node, argv_t *argv_struc, int last_pos);
bool skip_parenthese(tree_t *node, char **argv, int *last_pos);
bool is_inhibitor(const char c);
char *inhibitor_parse(type_list_t type, const char *str, int *index, int *len);
argv_t *copy_basic_words(
    int *i, argv_t *argv_struct, char const *str, int *word_i);
void inhibitor_handle(
    const char *str, int *i, argv_t *argv_struct, int *word_index);
void metacharacter_handle(
    const char *str, int *i, argv_t *argv_struct, int *word_index);
void free_argv_t(argv_t *argv_struct);
bool inhibitor_error(argv_t *argv_struct);
/* alias */
alias_t *create_alias_node(const char *name, const char *command);
void add_alias(alias_t **head, const char *name, const char *command);
char *find_alias(alias_t *head, const char *name);
int delete_alias(alias_t **head, const char *name);
void free_alias_list(alias_t *head);
int alias_handler(
    core_t *core, argv_t *argv_struct, int input_fd, int output_fd);
int unalias_handler(
    core_t *core, argv_t *argv_struct, int input_fd, int output_fd);
argv_t *get_alias_expansion(core_t *core, char *command);
int exec_alias(core_t *core, argv_t *alias_expansion, int input, int output);
void inhibitor_handle(const char *str, int *i, argv_t *argv_struct,
    int *word_index);
argv_t *input_line_parser(char const *str);
bool inhibitor_error(argv_t *argv_struct);
type_list_t determine_type(const char c);
argv_t *copy_basic_words(int *i, argv_t *argv_struct,
    char const *str, int *word_i);
void metacharacter_handle(const char *str, int *i,
    argv_t *argv_struct, int *word_index);

//line edition
char *get_input(void);
int up_arrow(int *char_index, bool *escape_sequence);
int down_arrow(int *char_index, bool *escape_sequence);
int left_arrow(int *char_index, bool *escape_sequence);
int right_arrow(int *char_index, bool *escape_sequence, char *input);

//job control
int add_to_job_stack(job_list_t **head, pid_t process, char *command);
void pop_job_stack(job_list_t **head, job_list_t *to_delete);
void update_jobs(core_t *core, bool);
void print_job(job_list_t *job, int output_fd);
int jobs_handler(core_t *core, argv_t *argv, int in, int out);
void free_jobs(job_list_t *head);
int fg_handler(core_t *core, argv_t *argv, int in, int out);

//history handle
argv_t *history_replace(core_t *core, argv_t *old_argv_struct, int index);
char *find_hist_content(char *name, hist_list_t *last);
void history_parse(core_t *core);
FILE *open_file(core_t *core);
void add_to_hist_list(hist_list_t **head, hist_list_t **last,
    char **argv, FILE *file);
void parse_add_hist_list(char *str, hist_list_t **head, hist_list_t **last);
bool contains_history_command(core_t *core, argv_t *argv_struct);
void history_handle(core_t *core, argv_t *argv_struct);
void free_history(hist_list_t *hist_head);
bool is_history_str(char *str);

//miscellaneous

void main_loop(core_t *core);
char **my_str_to_word_array_specific(char const *str, char spec_letter);
char *first_char(const char *str, const char c);
tree_t *tree_parser(core_t *core, argv_t *argv_struct);
tree_t *recursive_parse(argv_t *argv_struct);
int free_tree(tree_t *root);
void reset_sub_input(core_t *core);
void no_environment(core_t *core);
void update_shlvl(core_t *core);
int recursive_error_check(core_t *core, tree_t *node);
bool entrenchment_error_finder(core_t *core, char **argv);
void free_argv_t(argv_t *argv_struct);

#endif
