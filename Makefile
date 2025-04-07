##
## EPITECH PROJECT, 2024
## My_printf
## File description:
## Makefile
##

LIB_NAME = libmy.a
NAME = mysh
TEST_BIN = unit_tests

SRC = ./main.c \
	./src/builtins/change_dir/cd_handler.c \
	./src/builtins/environment/env_handler.c \
	./src/builtins/environment/env_list.c \
	./src/builtins/echo/echo_handler.c \
	./src/loop/prompt_loop.c \
	./src/command_execution/execution_handler.c \
	./src/command_execution/path_finder.c \
	./src/command_execution/leaf_execution.c \
	./src/tree_handler/tree_maker/command_separator.c \
	./src/tree_handler/tree_maker/operators.c \
	./src/tree_handler/tree_executor/leaf_handler.c \
	./src/tree_handler/tree_executor/recursive_execute.c \
	./src/tree_handler/tree_executor/redirector.c \
	./src/tree_handler/tree_executor/write_pipefd.c \
	./src/tree_handler/type_handler/handle_redirection.c \
	./src/tree_handler/type_handler/pipe/pipe_redirection.c \
	./src/tree_handler/type_handler/input_redirection/left_append.c \
	./src/tree_handler/type_handler/input_redirection/left_shift.c \
	./src/tree_handler/type_handler/output_redirection/right_append.c \
	./src/tree_handler/type_handler/output_redirection/right_shift.c \
	./src/tree_handler/print_tree.c \
	./src/tree_handler/free_tree.c \
	./src/utils/str_to_word_array_specific.c \
	./src/utils/first_char.c \
	./src/utils/my_cooler_putstr.c \
	./src/utils/my_put_nbr.c \
	./src/utils/str_to_word_array.c \
	./src/utils/last_char.c \
	./src/utils/my_num_to_str.c \
	./src/utils/my_numlen.c \
	./src/utils/my_revstr.c \
	./src/utils/my_strcat.c \
	./src/utils/my_strcpy.c \
	./src/utils/my_str_to_int.c \
	./src/utils/my_strlen.c \
	./src/utils/my_strncpy.c \
	./src/utils/my_str_to_float.c \
	./src/utils/my_strncmp.c \
	./src/utils/my_move_to_char.c \
	./src/utils/my_strtok.c \
	./src/utils/my_int_to_str.c \
	./src/utils/ascii_to_sum.c \
	./src/utils/my_strcmp.c \
	./src/utils/my_strdup.c \
	./src/utils/list_to_array.c \
	./src/utils/free_array.c \
	./src/utils/print_array.c \

TEST_SRC = $(SRC) \
	./unit_tests/unit_test_minishell.c

CC = gcc
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -g
INCLUDE_PATH = ./include/
LDFLAGS = -I$(INCLUDE_PATH)
TEST_LDFLAGS = $(LDFLAGS) --coverage -lcriterion
DESTINATION = -I$(INCLUDE_PATH) -L. -lmy

all: $(LIB_NAME) $(NAME)

$(NAME): $(LIB_NAME)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(DESTINATION)

$(LIB_NAME): $(OBJ)
	ar -rc $(LIB_NAME) $(OBJ)

$(TEST_BIN):
	$(CC) $(CFLAGS) -o $(TEST_BIN) $(TEST_SRC) $(TEST_LDFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJ)
	rm -f *.gc*

fclean: clean
	rm -f $(LIB_NAME)
	rm -f $(NAME)
	rm -f $(TEST_BIN)

re: fclean $(LIB_NAME) $(NAME)

compile:
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS)

coverage: tests_run
	gcovr -r .
	gcovr -r . --branches

.PHONY: all re compile coverage fclean clean tester
