/*
** EPITECH PROJECT, 2024
** fake_my_hunter
** File description:
** my
*/

#ifndef INCLUDED_MY_H
    #define INCLUDED_MY_H
    #include <stdlib.h>
    #include "struct.h"
    #include <unistd.h>
    #include <fcntl.h>
    #include <dirent.h>
    #include <string.h>
    #include <string.h>
    #include <sys/types.h>
    #include <time.h>
    #include <sys/wait.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <sys/stat.h>

    #define READ 0
    #define WRITE 1


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
int argc_counter(char **array);
int print_array(char **array);
int binary_handler(char **argv, char **env, core_t *core);
void main_loop(core_t *core);
int free_array(char **array);
env_t *parse_env(char **env);
int modify_content(env_t **head, const char *name, const char *new_content);
void add_to_list(env_t **head, const char *name, const char *content);
void free_list(env_t *head);
int print_env(core_t *core, char **argv);
int delete_node(env_t **head, const char *name);
char *find_content(env_t *head, const char *name);
int cd_handler(core_t *core, char **argv);
char **list_to_array(env_t *head);
char **my_str_to_word_array_specific(char const *str, char spec_letter);
char *first_char(const char *str, const char c);
char *find_path(char **argv, core_t *core);
int setenv_direct(core_t *core, char **argv);
int unsetenv_direct(core_t *core, char **argv);
int echo_handler(core_t *core, char **argv);
tree_t *tree_parser(char **argv);
int print_tree(tree_t *root);
tree_t *recursive_parse(char **argv);
int free_tree(tree_t *root);
int leaf_executor(core_t *core, int pipe_to_child, int pipe_from_child);
int handle_redirection(core_t *core, tree_t *node, int in_fd, int out_fd);
int right_shift(core_t *core, tree_t *node, int input, int output);
void reset_sub_input(core_t *core);
int right_append(core_t *core, tree_t *node, int input, int output);
int execute_node(core_t *core, tree_t *node, int input_fd, int output_fd);
int left_shift(core_t *core, tree_t *node, int input, int output);
int leaf_handler(core_t *core, char **argv, int input, int output);
int execute_node(core_t *core, tree_t *node, int input_fd, int output_fd);
int check_system_commands(core_t *core, char **argv);
int left_append(core_t *core, tree_t *node, int input, int output);
void handle_pipe(core_t *core, tree_t *node, int input_fd, int output_fd);
#endif
