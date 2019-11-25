/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_commands.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2060/00/00 18:14:45 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/24 03:04:45 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "taskmaster.h"

void	ft_cmd_start(t_tm *tm, char *name)
{
	int			i;
	t_status	*status;

	ft_sprintf(&tm->ret, "starting: [%s]\n", name);
	i = -1;
	printf("\nJOBS_COUNT: [%d]\n", tm->jobs_cnt);
	while (++i < tm->jobs_cnt)
		if (!ft_strcmp(name, tm->jobs[i].name) || !ft_strcmp(name, "all"))
		{
			status = &tm->shared->status[i];
			while (status)
			{
				status->retries = 0;
				status = status->next;
			}
			status = &tm->shared->status[i];
			if (status->state == paused)
				while (status)
				{
					kill(status->pid, SIGCONT);
					status->state = running;
					status = status->next;
				}
			else if (status->state == stopped || status->state == error)
				ft_exec_job(tm, i, -1);
		}
}

void	ft_cmd_pause(t_tm *tm, char *name)
{
	int			i;
	t_status	*status;

	ft_sprintf(&tm->ret, "pausing: [%s]\n", name);
	i = -1;
	printf("\nJOBS_COUNT: [%d]\n", tm->jobs_cnt);
	while (++i < tm->jobs_cnt)
		if ((!ft_strcmp(name, tm->jobs[i].name) || !ft_strcmp(name, "all")) &&
			tm->shared->status[i].pid > 0)
		{
			status = &tm->shared->status[i];
			while (status)
			{
				if (status->state == running)
				{
					kill(status->pid, SIGSTOP);
					status->state = paused;
				}
				status = status->next;
			}
		}
}

void	ft_cmd_restart(t_tm *tm, char *name)
{
	int i;

	ft_sprintf(&tm->ret, "restarting: [%s]\n", name);
	i = -1;
	printf("\nJOBS_COUNT: [%d]\n", tm->jobs_cnt);
	while (++i < tm->jobs_cnt)
		if ((!ft_strcmp(name, tm->jobs[i].name) || !ft_strcmp(name, "all")))
			ft_restart_job(tm, i, &tm->shared->status[i]);
}

void	ft_cmd_status(t_tm *tm, char *name)
{
	int i;

	ft_sprintf(&tm->ret, "getting status of: [%s]\n", name);
	i = -1;
	printf("\nJOBS_COUNT: [%d]\n", tm->jobs_cnt);
	while (++i < tm->jobs_cnt)
		if (!ft_strcmp(name, tm->jobs[i].name) || !ft_strcmp(name, "all"))
			ft_get_job_status(tm, i, &tm->shared->status[i]);
}

void	ft_cmd_stop(t_tm *tm, char *name)
{
	int i;

	ft_sprintf(&tm->ret, "stopping: [%s]\n", name);
	i = -1;
	printf("\nJOBS_COUNT: [%d]\n", tm->jobs_cnt);
	while (++i < tm->jobs_cnt)
		if (!ft_strcmp(name, tm->jobs[i].name) || !ft_strcmp(name, "all"))
			ft_stop_job(tm, i, &tm->shared->status[i]);
}
