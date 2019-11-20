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

static int	ft_change_fd(int fd, char *path)
{
	int tmp_fd;
	int ret;

	if (!path && path[0])
		return (-1);
	if ((tmp_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
		return (-1);
	ret = dup2(tmp_fd, fd);
	close(tmp_fd);
	return (ret);
}

static void	ft_monitor_process(t_tm *tm, t_status *status, int id_job,
																	int id_proc)
{
	int child_status;

	status->started_time = time(NULL);
	wait(&child_status);
	status->stopped_time = time(NULL);
	if ((WIFEXITED(child_status) && !ft_memchr(tm->jobs[id_job].exit_codes,
		WEXITSTATUS(child_status), sizeof(tm->jobs[id_job].exit_codes))) ||
		(WIFSIGNALED(child_status) &&
						WTERMSIG(child_status) != tm->jobs[id_job].stop_signal))
		status->state = error;
	else if (status->state != error)
		status->state = stopped;
	if (tm->jobs[id_job].autorestart && status->can_restart &&
						status->retries < tm->jobs[id_job].start_retries)
	{
		status->retries++;
		ft_exec_job(tm, id_job, id_proc);
	}
}

static void	ft_exec_job_inner(t_tm *tm, int id_job, t_status *status,
																	int id_proc)
{
	pid_t	father;
	char	**args;

	args = ft_strsplit(tm->jobs[id_job].cmd, ' ');
	ft_change_fd(STDOUT_FILENO, tm->jobs[id_job].stdout);
	ft_change_fd(STDERR_FILENO, tm->jobs[id_job].stderr);
	if (tm->jobs[id_job].stderr[0])
		umask(tm->jobs[id_job].stderr[0]);
	if (tm->jobs[id_job].working_dir[0])
		chdir(tm->jobs[id_job].working_dir);
	if (!(father = fork()))
	{
		status->state = starting;
		if (args && execve(args[0], args, tm->jobs[id_job].env) < 0)
			ft_sprintf(&tm->ret, "{red}Error starting '%s'{eoc}\n",
														tm->jobs[id_job].name);
		status->state = error;
		exit(127);
	}
	else
	{
		status->pid = father;
		ft_monitor_process(tm, status, id_job, id_proc);
		ft_free_list(args);
	}
}

static void	ft_check_starttime(t_tm *tm, t_status *status, int id_job,
																	int id_proc)
{
	ft_sleep(tm->jobs[id_job].start_time);
	if (status->pid > 0 && kill(status->pid, 0) > -1)
		status->state = running;
	else if (status->state != stopped &&
				status->retries < tm->jobs[id_job].start_retries)
	{
		status->retries++;
		ft_exec_job(tm, id_job, id_proc);
	}
	else if (status->state != error)
		status->state = stopped;
}

void		ft_exec_job(t_tm *tm, int id_job, int id_retry)
{
	pid_t		father;
	t_status	*status;
	int			i;

	status = &tm->shared->status[id_job];
	i = -1;
	while (++i < tm->jobs[id_job].nb_procs && status)
	{
		if ((id_retry == -1 || id_retry == i) && !fork())
		{
			father = fork();
			if (!father)
			{
				ft_exec_job_inner(tm, id_job, status, i);
			}
			else
				ft_check_starttime(tm, status, id_job, i);
			exit(0);
		}
		status = status->next;
	}
	if (id_retry > -1)
		exit(0);
}
