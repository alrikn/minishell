/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** cd_handler
*/


#include "my.h"
#include "struct.h"
#include <stdio.h>
#include <stdlib.h>

char *path_finder(core_t *core)
{
    return 0;
}

int cd_home(core_t *core, char **argv)
{
    char *home_path = find_content(core->head, "HOME");
    char *old_pwd = find_content(core->head, "PWD");

    if (!home_path) {
        my_cooler_putstr("cd: HOME not set\n");
        return 1;
    }
    if (chdir(home_path) != 0) {
        perror("cd");
        core->exit.last_failed = true;
        return 1;
    }
    modify_content(&core->head, "OLDPWD", old_pwd);
    modify_content(&core->head, "PWD", home_path);
    return 0;
}

int cd_minus(core_t *core, char **argv)
{
    char *oldpwd = my_strdup(find_content(core->head, "OLDPWD"));
    char *current_pwd = find_content(core->head, "PWD");

    if (!oldpwd) {
        perror("cd: OLDPWD not set\n");
        return 1;
    }
    if (chdir(oldpwd) != 0) {
        perror("cd");
        return 1;
    }
    modify_content(&core->head, "OLDPWD", current_pwd);
    modify_content(&core->head, "PWD", oldpwd);
    my_cooler_putstr(oldpwd);
    my_cooler_putstr("\n");
    free(oldpwd);
    return 0;
}

int cd_somewhere(core_t *core, char **argv)
{
    char *target = argv[1];
    char *old_pwd = find_content(core->head, "PWD");
    char cwd[PATH_MAX];

    if (chdir(target) != 0) {
        my_cooler_putstr(target);
        my_cooler_putstr(": Not a directory.\n");
        return 1;
    }
    if (!getcwd(cwd, sizeof(cwd))) {
        perror("cd");
        return 1;
    }
    modify_content(&core->head, "OLDPWD", old_pwd);
    modify_content(&core->head, "PWD", cwd);
    return 0;
}

/*
 ** this function is a one serves all. it does cd, cd -, cd ~, cd somewhere
 ** TODO: for now cd ~ does the same thing as cd but this will have to change
 ** TODO:if they remove HOME we are kinda fucked i have to check in passwd file
*/
int cd_handler(core_t *core, char **argv)
{
    int argc = argc_counter(argv);

    if (argc > 2) {
        my_cooler_putstr("cd: too many arguments\n");
        return 1;
    }
    if (argc == 1) {
        return cd_home(core, argv);
    }
    if (my_strcmp(argv[1], "-") == 0) {
        return cd_minus(core, argv);
    }
    if (argv[1][0] == '~') {
        return cd_home(core, argv);
    }
    return cd_somewhere(core, argv);
}
