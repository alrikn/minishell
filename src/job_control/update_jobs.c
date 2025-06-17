/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** update_jobs.c
*/

#include "my.h"
#include "struct.h"
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int check_to_delete(job_list_t *job, core_t *core, bool from_print)
{
    if (WIFSTOPPED(job->prev_signal) || WIFCONTINUED(job->prev_signal))
        return 1;
    if (WIFEXITED(job->prev_signal) || WIFSIGNALED(job->prev_signal)) {
        if ((!from_print || !job->just_added) && !(core->job.called_jobs))
            print_job(job, STDOUT_FILENO);
        pop_job_stack(&core->job.job_head, job);
        return 1;
    }
    return 0;
}

void update_jobs(core_t *core, bool from_print)
{
    job_list_t *current_node = core->job.job_head;
    job_list_t *next_node;
    int current_signal = 0;

    if (!current_node)
        return;
    while (current_node) {
        next_node = current_node->next;
        if (check_to_delete(current_node, core, from_print)) {
            current_node = next_node;
            continue;
        }
        current_node->just_added = false;
        if (waitpid(current_node->current_job, &current_signal, WNOHANG
            | WUNTRACED | WCONTINUED) > 0)
            current_node->prev_signal = current_signal;
        current_node = next_node;
        core->job.called_jobs = false;
    }
}
