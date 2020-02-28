/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_status.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 05:53:35 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 05:53:35 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster.h"

void		ft_init_status(t_status *status)
{
	status->pid = 0;
	status->state = stopped;
	status->started_time = 0;
	status->stopped_time = 0;
	status->retries = 0;
	status->can_restart = 1;
	status->next = NULL;
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
		ft_sprintf(&tm->ret, "%s%s ", tm->ret, "\e[91m");
	else if (status->state == starting)
		ft_sprintf(&tm->ret, "%s%s ", tm->ret, "\e[38;5;208m");
	else if (status->state == running)
		ft_sprintf(&tm->ret, "%s%s ", tm->ret, "\e[92m");
	else if (status->state == paused)
		ft_sprintf(&tm->ret, "%s%s ", tm->ret, "\e[93m");
	else if (status->state == error)
		ft_sprintf(&tm->ret, "%s%s ", tm->ret, "\e[41m");
	ft_sprintf(&tm->ret, "%s%-20s ", tm->ret, tm->jobs[id_job].name);
	if (status->state == stopped)
		ft_sprintf(&tm->ret, "%s%-8s ", tm->ret, "STOPPED");
	else if (status->state == starting)
		ft_sprintf(&tm->ret, "%s%-8s ", tm->ret, "STARTING");
	else if (status->state == running)
		ft_sprintf(&tm->ret, "%s%-8s ", tm->ret, "RUNNING");
	else if (status->state == paused)
		ft_sprintf(&tm->ret, "%s%-8s ", tm->ret, "PAUSED");
	else if (status->state == error)
		ft_sprintf(&tm->ret, "%s%-8s ", tm->ret, "ERROR");
	if (status->retries)
		ft_sprintf(&tm->ret, "%s(%d retries)  ", tm->ret, status->retries);
	else
		ft_sprintf(&tm->ret, "%s             ", tm->ret);
}

void		ft_get_job_status(t_tm *tm, int id_job, t_status *status)
{
	t_htime htime;

	ft_print_name_and_state(tm, id_job, status);
	if (status->pid > 0 && status->state && status->state != error)
		ft_sprintf(&tm->ret, "%spid %-10d", tm->ret, status->pid);
	else
		ft_sprintf(&tm->ret, "%spid %-10s", tm->ret, "N/A");
	if (status->state > stopped && status->state < error)
	{
		ft_get_htime(&htime, time(NULL) - status->started_time);
		ft_sprintf(&tm->ret, "%suptime    %02d:%02d:%02d",
											tm->ret, htime.h, htime.m, htime.s);
	}
	else if (status->stopped_time)
	{
		ft_get_htime(&htime, time(NULL) - status->stopped_time);
		ft_sprintf(&tm->ret, "%sdowntime  %02d:%02d:%02d",
											tm->ret, htime.h, htime.m, htime.s);
	}
	else
		ft_sprintf(&tm->ret, "%suptime    N/A", tm->ret);
	ft_sprintf(&tm->ret, "%s {eoc}\n", tm->ret);
	if (status->next)
		ft_get_job_status(tm, id_job, status->next);
}
