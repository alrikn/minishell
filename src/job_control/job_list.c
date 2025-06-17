/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** job_list.c
*/

#include "my.h"
#include "struct.h"
#include <stdlib.h>
#include <sys/wait.h>

static void adding_job_info(pid_t process, char *command, job_list_t *job)
{
    int new_signal = 0;

    job->prev_signal = -1;
    job->current_job = process;
    job->command = command;
    job->job_priority = J_FIRST;
    job->just_added = true;
    if (waitpid(process, &new_signal, WNOHANG | WUNTRACED | WCONTINUED) > 0)
        job->prev_signal = new_signal;
}

int add_to_job_stack(job_list_t **head, pid_t process, char *command)
{
    job_list_t *new_head = calloc(1, sizeof(job_list_t));

    if (!new_head)
        return 0;
    adding_job_info(process, command, new_head);
    if (*head == NULL) {
        *head = new_head;
        (*head)->job_nbr = 1;
        (*head)->next = NULL;
        (*head)->prev = NULL;
        return 1;
    }
    new_head->next = *head;
    new_head->job_nbr = (*head)->job_nbr + 1;
    (*head)->prev = new_head;
    *head = new_head;
    return 1;
}

void free_jobs(job_list_t *head)
{
    while (head)
        pop_job_stack(&head, head);
}

void pop_job_stack(job_list_t **head, job_list_t *to_delete)
{
    job_list_t *prev_job;
    job_list_t *next_job;

    if (!to_delete)
        return;
    prev_job = to_delete->prev;
    next_job = to_delete->next;
    if (*head == to_delete) {
        *head = next_job;
    }
    if (prev_job)
        prev_job->next = next_job;
    if (next_job)
        next_job->prev = prev_job;
    if (to_delete->command)
        free(to_delete->command);
    free(to_delete);
    return;
}
