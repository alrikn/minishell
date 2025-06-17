/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** inhibitor_parser
*/

#include "my.h"
#include "struct.h"

static int len_getter(const char *str, int *index, int list)
{
    int len = 0;

    while (str[*index] && str[*index] != MY_INHIBITORS[list].letter) {
        len++;
        *index += 1;
    }
    return len;
}

static char *inhibitor_error_message(type_list_t type)
{
    if (type == SING_QUOTE)
        my_cooler_putstr("Unmatched \'\'\'.\n");
    if (type == DOUBL_QUOTE)
        my_cooler_putstr("Unmatched \'\"\'.\n");
    if (type == BACKTICK)
        my_cooler_putstr("Unmatched \'`\'.\n");
    return NULL;
}

/*
** here we deal with backticks etc
** returns null for error
**we will also have to print error message here
** does not expect to be on an inhibitor
** will leave you on an inhibitor
*/
char *inhibitor_parse(type_list_t type, const char *str, int *index, int *len)
{
    char *result = NULL;
    int list = 0;
    int original_pos = *index;
    int i = 0;

    if (type == NORM || type == NONE || type == ERROR)
        return NULL;
    while (MY_INHIBITORS[list].type != type)
        list++;
    *len = len_getter(str, index, list);
    if (str[*index] != MY_INHIBITORS[list].letter)
        return inhibitor_error_message(type);
    result = malloc(sizeof(char) * (*len + 1));
    for (i = 0; str[original_pos] && original_pos < *index; i++) {
        result[i] = str[original_pos];
        original_pos++;
    }
    result[i] = '\0';
    return result;
}

bool is_inhibitor(const char c)
{
    if (c == '\'' || c == '"' || c == '`')
        return true;
    return false;
}

/*
** returns norm if it isnt an inhibitor
*/
type_list_t determine_type(const char c)
{
    if (c == '\'')
        return SING_QUOTE;
    if (c == '"')
        return DOUBL_QUOTE;
    if (c == '`')
        return BACKTICK;
    return NORM;
}
