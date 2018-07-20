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

void	ft_stop_job(t_tm *tm, int id_job, t_status *status)
{
	pid_t	father;

	if (!status->pid)
		return ;
	father = fork();
	if (!father)
	{
		kill(status->pid, tm->jobs[id_job].stop_signal);
		ft_sleep(tm->jobs[id_job].stop_signal);
		if (status->pid > 0 && kill(status->pid, 0) > -1)
			kill(status->pid, 9);
		if (status->pid > 0 && kill(status->pid, 0) == -1)
		{
			status->state = stopped;
			status->stopped_time = time(NULL);
		}
		exit(0);
	}
	else if (status->next)
		ft_stop_job(tm, id_job, status->next);
}

void	ft_cmd_start(t_tm *tm, char *name)
{
	int i;

	i = -1;
	while (++i < tm->jobs_cnt)
		if ((!ft_strcmp(name, tm->jobs[i].name) || !ft_strcmp(name, "all")) &&
			tm->shared->status[i].state == stopped)
			ft_exec_job(tm, i);
}

void	ft_cmd_restart(t_tm *tm, char *name)
{
	int i;

	i = -1;
	while (++i < tm->jobs_cnt)
		if ((!ft_strcmp(name, tm->jobs[i].name) || !ft_strcmp(name, "all")))
		{
			kill(tm->shared->status[i].pid, tm->jobs[i].stop_signal);
			ft_exec_job(tm, i);
		}
}

void	ft_cmd_status(t_tm *tm, char *name)
{
	int i;

	i = -1;
	while (++i < tm->jobs_cnt)
		if (!ft_strcmp(name, tm->jobs[i].name) || !ft_strcmp(name, "all"))
			ft_get_job_status(tm, i, &tm->shared->status[i]);
		//	ft_get_job_status(tm, i);
}

void	ft_cmd_stop(t_tm *tm, char *name)
{
	int i;

	i = -1;
	while (++i < tm->jobs_cnt)
		if (!ft_strcmp(name, tm->jobs[i].name) || !ft_strcmp(name, "all"))
			ft_stop_job(tm, i, &tm->shared->status[i]);
}