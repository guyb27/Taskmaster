/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_jobs_funcs.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/19 22:41:54 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/24 03:09:00 by gmadec      ###    #+. /#+    ###.fr     */
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
		status->can_restart = 0;
		kill(status->pid, tm->jobs[id_job].stop_signal);
		ft_sleep(tm->jobs[id_job].stop_signal);
		if (status->pid > 0 && kill(status->pid, 0) > -1)
			kill(status->pid, 9);
		status->can_restart = 1;
		if (status->pid > 0 && kill(status->pid, 0) == -1)
		{
			status->state = stopped;
			status->stopped_time = time(NULL);
		}
		exit(0);
	}
	if (status->next)
		ft_stop_job(tm, id_job, status->next);
}

void	ft_restart_job(t_tm *tm, int id_job, t_status *status)
{
	if (status->pid)
		kill(status->pid, 9);
	status->retries = 0;
	if (status->next)
		ft_restart_job(tm, id_job, status->next);
	else
		ft_exec_job(tm, id_job, -1);
}

void	ft_autostart_jobs(t_tm *tm)
{
	int i;

	i = -1;
	printf("JOBS_COUNT: [%d]\n", tm->jobs_cnt);
	while (++i < tm->jobs_cnt)
	{
		if (tm->jobs[i].autostart == 1)
			ft_exec_job(tm, i, -1);
	}
}
