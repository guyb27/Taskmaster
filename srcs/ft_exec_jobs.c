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

void	logprint(char *str)
{
	char tmp[2048];
	sprintf(tmp, "echo \"%s\" >> /tmp/gmadec.log", str);
	system(tmp);
}

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
/*
char	*ft_strchrFUCK(const char *s, int c)
{
	while (*s)
	{
		char tmp2[1024];
		sprintf(tmp2, "comp %d %d %d", *s, c, (char)c);
		logprint(tmp2);
		if (*s == (char)c)
			return ((char *)s);
		else
			s++;
	}
	return (c == '\0' ? (char *)s : NULL);
} */

static void	ft_monitor_process(t_tm *tm, t_status *status, int id_job,
																	int id_proc)
{
	int child_status;

	//logprint("BONJOUR\n");
	char tmp1[1024];
	sprintf(tmp1, "1BONJOUR lol %d", status->pid);
	logprint(tmp1);


	status->started_time = time(NULL);
//	wait(&status->pid);
	wait(&child_status);
	status->stopped_time = time(NULL);

	char tmp[1024];
	sprintf(tmp, "----> %d %d %d %d %d %d %d %d", 	WIFEXITED(child_status), 
														WEXITSTATUS(child_status),
													WIFSIGNALED(child_status),
														WTERMSIG(child_status),
													WCOREDUMP(child_status),
													WIFSTOPPED(child_status), 
														WSTOPSIG(child_status),
													WIFCONTINUED(child_status));
	logprint(tmp);

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

/*********************************************************************/
void	ft_copy_env(char ***new_env, char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	*new_env = malloc((i + 1) * sizeof(char *));
	i = -1;
	while (env[++i])
		(*new_env)[i] = ft_strdup(env[i]);
	(*new_env)[i] = NULL;
}

void	ft_unsetenv(char ***env, char *name)
{
	int i;

	i = 0;
	while ((*env)[i])
		if (!ft_strncmp((*env)[i], name, ft_strlen(name)))
			break ;
		else
			i++;
	while ((*env)[i])
	{
		free((*env)[i]);
		if ((*env)[i + 1])
			(*env)[i] = ft_strdup((*env)[i + 1]);
		else
			(*env)[i] = NULL;
		i++;
	}
}

void	ft_setenv(char ***env, char *name, char *value)
{
	int		i;
	char	*new_var;

	ft_unsetenv(env, name);
	i = 0;
	while ((*env)[i])
		i++;
	new_var = NULL;
	if (value[0] == '"' && value[ft_strlen(value) - 1] == '"')
		ft_sprintf(&new_var, "%s=%.*s", name, ft_strlen(value) - 2, value + 1);
	else
		ft_sprintf(&new_var, "%s=%s", name, value);
	(*env)[i] = new_var;
	(*env)[i + 1] = NULL;
}
/*********************************************************************/

static void	ft_exec_job_inner(t_tm *tm, int id_job, t_status *status,
																	int id_proc)
{
	pid_t	father;
	char	**args;

	args = NULL;
	args = ft_strsplit(tm->jobs[id_job].cmd, ' ');
	ft_change_fd(STDOUT_FILENO, tm->jobs[id_job].stdout);
	ft_change_fd(STDERR_FILENO, tm->jobs[id_job].stderr);
	if (tm->jobs[id_job].stderr[0])
		umask(tm->jobs[id_job].stderr[0]);
	if (tm->jobs[id_job].working_dir[0])
		chdir(tm->jobs[id_job].working_dir);

	if (!(father = fork()))
	{
//char tmp1[1024];
//sprintf(tmp1, "env %s=%s", getenv("FUCKER"), getenv("ANSWER"));
//logprint(tmp1);
		char **new_env;
		new_env = NULL;
		ft_copy_env(&new_env, tm->env);
		ft_setenv(&new_env, "FUCKER", "awesome");

		char tmp1[1024];
		sprintf(tmp1, "env[0]: [%s]", new_env[0]);
		logprint(tmp1);

		status->state = starting;
		if (args && execve(args[0], args, new_env) < 0)
			ft_printf("{red}Error starting '%s'{eoc}\n", tm->jobs[id_job].name);
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
	t_keyval	*tmp;

	status = &tm->shared->status[id_job];
	i = -1;
	while (++i < tm->jobs[id_job].nb_procs && status)
	{
		if ((id_retry == -1 || id_retry == i) && !fork())
		{
			
			
			tmp = tm->jobs[id_job].env;
			while (tmp)
			{
				
				setenv(tmp->key, tmp->value, 1);
				tmp = tmp->next;
			}


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
