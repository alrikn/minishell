/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** getline_display.c
*/

#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "my.h"

static char *add_to_buff(char *buff, char new_char, int char_index)
{
    char *new_buff = calloc(strlen(buff) + 2, 1);

    if (!new_buff)
        return buff;
    for (int i = 0; i < char_index; i++)
        new_buff[i] = buff[i];
    new_buff[char_index] = new_char;
    for (int i = char_index; i < strlen(buff); i++)
        new_buff[i + 1] = buff[i];
    free(buff);
    return new_buff;
}

static char *remove_from_buff(char *buff, int char_index)
{
    char *new_buff = calloc(strlen(buff) + 1, 1);

    if (!new_buff)
        return buff;
    for (int i = 0; i < char_index; i++)
        new_buff[i] = buff[i];
    for (int i = char_index + 1; i < strlen(buff); i++)
        new_buff[i - 1] = buff[i];
    free(buff);
    return new_buff;
}

int handle_escape(char c, char *input, int *char_index, bool *escape_sequence)
{
    switch (c) {
        case UP_ARROW:
            return up_arrow(char_index, escape_sequence);
        case DOWN_ARROW:
            return down_arrow(char_index, escape_sequence);
        case LEFT_ARROW:
            return left_arrow(char_index, escape_sequence);
        case RIGHT_ARROW:
            return right_arrow(char_index, escape_sequence, input);
    }
    return 0;
}

int handle_char(char c, char **input, int *char_index, bool *escape_sequence)
{
    if (c == ESC)
        *escape_sequence = true;
    if (*escape_sequence)
        return handle_escape(c, *input, char_index, escape_sequence);
    if (c == DEL) {
        if (*char_index > 0) {
            (*char_index)--;
            *input = remove_from_buff(*input, *char_index);
            return -1;
        }
    } else {
        *input = add_to_buff(*input, c, *char_index);
        (*char_index)++;
        return 1;
    }
    return 0;
}

static void set_terminal_settings(void)
{
    struct termios attr;

    if (!isatty(STDIN_FILENO))
        return;
    printf("$> ");
    tcgetattr(STDIN_FILENO, &attr);
    attr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &attr);
}

static int display_input(char *input, int char_change, int char_index,
    int prev_length)
{
    int input_len = strlen(input);

    if (!isatty(STDIN_FILENO))
        return input_len;
    if (prev_length == -1)
        prev_length = input_len - char_change;
    for (int i = char_index - char_change; i < prev_length; i++) {
        printf("\033[C");
        fflush(stdout);
    }
    for (int i = 0; i < prev_length; i++) {
        printf("\b \b");
        fflush(stdout);
    }
    printf("%s", input);
    for (int i = char_index; i < input_len; i++) {
        printf("\033[D");
        fflush(stdout);
    }
    return input_len;
}

static char *text_disruption(char current_char, char *input)
{
    if (!isatty(STDIN_FILENO) && current_char == -1) {
        free(input);
        return NULL;
    }
    if (current_char == '\n') {
        printf("\n");
        return input;
    }
    if (input)
        free(input);
    printf("\n");
    if (current_char == EOT)
        return NULL;
    return strdup("\n");
}

char *get_input(void)
{
    int prev_length = -1;
    char current_char = 0;
    int char_index = 0;
    int char_change = 0;
    bool escape_sequence = false;
    char *input = calloc(1, 1);

    set_terminal_settings();
    while (current_char != '\n' && current_char != -1 && input) {
        current_char = getchar();
        if (current_char == EOT || current_char == ETX || current_char == -1 ||
                current_char == '\n')
            return text_disruption(current_char, input);
        char_change = handle_char(current_char, &input, &char_index,
            &escape_sequence);
        prev_length = display_input(input, char_change, char_index,
            prev_length);
    }
    return input;
}
