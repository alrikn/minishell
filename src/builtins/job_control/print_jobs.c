/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** print_jobs.c
*/

#include "my.h"
#include "struct.h"
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

void print_job(job_list_t *job, int output_fd)
{
    char priority_chars[J_NONE + 1] = "+- ";
    char *str_status = "Running";
    char *core_dumped = "";

    if (WIFEXITED(job->prev_signal))
        str_status = "Done";
    if (WIFSIGNALED(job->prev_signal)) {
        str_status = strsignal(WTERMSIG(job->prev_signal));
        if (WCOREDUMP(job->prev_signal))
            core_dumped = " (core dumped)";
    }
    dprintf(output_fd, "[%d]  %c %-29s %s%s\n", job->job_nbr,
        priority_chars[job->job_priority], str_status, job->command,
        core_dumped);
}

int jobs_handler(core_t *core, argv_t *argv, int in, int out)
{
    job_list_t *last_job;

    update_jobs(core, true);
    last_job = core->job.job_head;
    if (!last_job)
        return 0;
    while (last_job->next)
        last_job = last_job->next;
    while (last_job->prev) {
        print_job(last_job, out);
        last_job = last_job->prev;
    }
    print_job(last_job, out);
    core->job.called_jobs = true;
    return 0;
}
