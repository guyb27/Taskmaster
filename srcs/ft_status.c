/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_commands.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2060/00/00 18:14:45 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2066/01/02 18:14:46 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "taskmaster.h"

void	ft_debug_status(t_status *status)
{
	ft_printf("pid:\t[%d]\n", status->pid);
	ft_printf("state:\t[%d]\n", status->state);
	ft_printf("stime:\t[%d]\n", status->started_time);
	ft_printf("ttime:\t[%d]\n", status->stopped_time);
}
//------------------------------------------------------------------------------

void	ft_init_status(t_status *status)
{
	status->pid = 0;
	status->state = stopped;
	status->started_time = 0;
	status->stopped_time = 0;
//	status->restarts = 0;
	status->next = NULL;
	status->prev = NULL;
}

static void	ft_get_htime(t_htime *htime, time_t time)
{
	if (time > 3600)
    {
        htime->m = time / 60;
        htime->h = htime->m / 60;
        htime->s = time % 60;
        htime->m = htime->m % 60;
    }
    else
    {
        htime->h = 0;
        htime->m = time / 60;
        htime->s = time % 60;
    }
}

void		ft_print_name_and_state(t_tm *tm, int id_job, t_status *status)
{
	if (status->state == stopped)
		ft_printf("%s ", "\e[91m");
	else if (status->state == starting)
		ft_printf("%s ", "\e[38;5;208m");
	else if (status->state == running)
		ft_printf("%s ", "\e[92m");
	else if (status->state == error)
		ft_printf("%s ", "\e[41m");
	ft_printf("%-20s ", tm->jobs[id_job].name);
	if (status->state == stopped)
		ft_printf("%-10s ", "STOPPED");
	else if (status->state == starting)
		ft_printf("%-10s ", "STARTING");
	else if (status->state == running)
		ft_printf("%-10s ", "RUNNING");
	else if (status->state == error)
		ft_printf("%-10s ", "ERROR");
//	ft_printf("state: [%d] ", status->state);
}

void	    ft_get_job_status(t_tm *tm, int id_job, t_status *status)
{
	t_htime htime;

//	ft_printf("%s", status->state ? "\e[92m" : "\e[91m");
//	ft_printf("%-20s ", tm->jobs[id_job].name);
//	ft_printf("%-10s ", status->state ? "RUNNING" : "STOPPED");
	ft_print_name_and_state(tm, id_job, status);
	if (status->pid > 0 && status->state && status->state != error)
		ft_printf("pid %-10d", status->pid);
	else
		ft_printf("pid %-10s", "N/A");
	if (status->state > stopped && status->state < error)
	{
		ft_get_htime(&htime, time(NULL) - status->started_time);
		ft_printf("uptime    %02d:%02d:%02d", htime.h, htime.m, htime.s);
	}
	else if (status->stopped_time)
	{
		ft_get_htime(&htime, time(NULL) - status->stopped_time);
		ft_printf("downtime  %02d:%02d:%02d", htime.h, htime.m, htime.s);
	}
	else
		ft_printf("uptime    N/A");
	ft_printf(" {eoc}\n");
	if (status->next)
		ft_get_job_status(tm, id_job, status->next);
}
/*
void	    ft_get_job_status(t_tm *tm, int id_job, t_status *status)
{
	t_status *tmp;
	t_htime htime;
	int i = 0;

	ft_get_htime(&htime, time(NULL) - 555);
	(void)tm;
	(void)id_job;
	tmp = status;
	while (tmp)
	{
		printf("-----------------------------------------\n");
		printf("Elem numero [%d], addr: [%p]\n", ++i, tmp);
		printf("pid: [%d]\n", tmp->pid);
		printf("next: [%p]\n", tmp->next);
		printf("prev: [%p]\n", tmp->prev);
		tmp = tmp->next;
	}
}*/


/*
void	    ft_get_job_status(t_tm *tm, int id_job)
{
	t_htime htime;

	ft_printf("%s", tm->shared->status[id_job].state ? "\e[92m" : "\e[91m");
	ft_printf("%-20s ", tm->jobs[id_job].name);
	ft_printf("%-10s ", tm->shared->status[id_job].state ? "RUNNING" : "STOPPED");
	if (tm->shared->status[id_job].pid > 0 && tm->shared->status[id_job].state)
		ft_printf("pid %-10d", tm->shared->status[id_job].pid);
	else
		ft_printf("pid %-10s", "N/A");
	if (tm->shared->status[id_job].state == running)
	{
		ft_get_htime(&htime, time(NULL) - tm->shared->status[id_job].started_time);
		ft_printf("uptime   %02d:%02d:%02d", htime.h, htime.m, htime.s);
	}
	else if (tm->shared->status[id_job].stopped_time)
	{
		ft_get_htime(&htime, time(NULL) - tm->shared->status[id_job].stopped_time);
		ft_printf("downtime %02d:%02d:%02d", htime.h, htime.m, htime.s);
	}
	else
		ft_printf("uptime   N/A");
	ft_printf("{eoc}\n");
	if (tm->shared->status[id_job].next)
		ft_get_job_status(tm, id_job);
}*/