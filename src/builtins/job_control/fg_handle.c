/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** fg_handle.c
*/

#include "my.h"
#include "struct.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static int correct_exit(int status, int out)
{
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    if (WIFSIGNALED(status)) {
        dprintf(out, "%s", strsignal(WTERMSIG(status)));
        if (WCOREDUMP(status))
            dprintf(out, " (core dumped)");
        dprintf(out, "\n");
        return status;
    }
    return 0;
}

int fg_handler(core_t *core, argv_t *argv, int in, int out)
{
    job_list_t *current_node = core->job.job_head;
    pid_t current_process;
    int signal = 0;

    if (!current_node) {
        dprintf(out, "fg: No current job\n");
        return 1;
    }
    current_process = current_node->current_job;
    if (WIFSTOPPED(current_node->prev_signal))
        kill(current_process, SIGCONT);
    dprintf(out, "%s\n", current_node->command);
    pop_job_stack(&core->job.job_head, core->job.job_head);
    waitpid(current_process, &signal, WUNTRACED);
    return correct_exit(signal, out);
}
