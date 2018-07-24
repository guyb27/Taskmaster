/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_exec_jobs.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2060/00/00 18:14:45 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2066/01/02 18:14:46 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "taskmaster.h"
/*
void		ft_remove_elem(t_status *status)
{
	t_status *tmp;

	if (!status)
		return ;
	tmp = status;
	if (tmp->prev)
	{
		tmp = tmp->prev;
		tmp->next = status->next;
	//	free(status);
		ft_megafree(status, sizeof(t_status));
	}
}*/

static void	ft_exec_job_inner(t_tm *tm, int id_job, t_status *status)
{
	pid_t	father;
	char	**args;
	int		fd_stdout;
	int		fd_stderr;

	args = NULL;
	args = ft_strsplit(tm->jobs[id_job].cmd, ' ');
	// stdout
	fd_stdout = 0;
	if (tm->jobs[id_job].stdout[0])
	{
		fd_stdout = open(tm->jobs[id_job].stdout, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd_stdout, STDOUT_FILENO);
	}
	// stderr
	fd_stderr = 0;
	if (tm->jobs[id_job].stderr[0])
	{
		fd_stderr = open(tm->jobs[id_job].stderr, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd_stderr, STDERR_FILENO);
	}
	// umask
	if (tm->jobs[id_job].stderr[0])
		umask(tm->jobs[id_job].stderr[0]);
    // workingdir
    if (tm->jobs[id_job].working_dir[0])
        chdir(tm->jobs[id_job].working_dir);
	father = fork();
	if (!father)
	{	
		status->state = starting;
		if (args && execve(args[0], args, tm->env) < 0)
			ft_printf("{red}Error executing '%s'{eoc}\n", tm->jobs[id_job].name);
		status->state = error;
		exit(0);
	}
	else
	{
		status->pid = father;
		status->started_time = time(NULL);
		if (status->state != error)
			status->state = starting;
		wait(&father);
		ft_free_list(args);
		status->stopped_time = time(NULL);
		if (status->state != error)
			status->state = stopped;
		if (fd_stdout > 0)
			close(fd_stdout);
		if (fd_stderr > 0)
			close(fd_stderr);
		ft_printf("program: [%s] just finished.\n", tm->jobs[id_job].name);
		exit(0);
	}
}

void		ft_exec_job(t_tm *tm, int id_job, int retry)
{
	pid_t		father;
	t_status	*status;
	int			i;

	ft_printf("executing: [%s]\n", tm->jobs[id_job].name);
	status = &tm->shared->status[id_job];
	i = -1;
	while (++i < tm->jobs[id_job].nb_procs && status)
	{
		father = fork();
		if (!father)
		{
			father = fork();
			if (!father)
				ft_exec_job_inner(tm, id_job, status);
			else
			{
				ft_sleep(tm->jobs[id_job].start_time);
				if (status->pid > 0 && kill(status->pid, 0) > -1)
					status->state = running;
				else if (status->retries < tm->jobs[id_job].start_retries)
				{
					status->retries++;
					ft_exec_job(tm, id_job, 1);
				}
			}
			exit(0);
		}
		status = status->next;
	}
	if (retry)
		exit(0);
}
