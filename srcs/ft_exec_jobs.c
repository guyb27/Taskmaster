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
/*	if (args)
	{
		tm->shared->status[id_job].started_time = time(NULL);
		tm->shared->status[id_job].state = running;
	}*/
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

//int fd = open("/tmp/lol.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
//ft_printf("wtf\n");
	father = fork();
    
	if (!father)
	{	
		status->state = starting;
		if (args && execve(args[0], args, tm->env) < 0)
			ft_printf("{red}Error executing '%s'{eoc}\n", tm->jobs[id_job].name);
		status->state = error;

	char *tmp7 = NULL;
	ft_sprintf(&tmp7, "echo shit an error occured for %s with state %d >> omg.log", tm->jobs[id_job].name, status->state);
	system(tmp7);

		exit(0);
	}
	else
	{
	//	ft_init_status(status);
		status->pid = father;
		status->started_time = time(NULL);
	//	status->state = running;
		if (status->state != error)
			status->state = starting;
		

	char *tmp8 = NULL;
	ft_sprintf(&tmp8, "echo started pid %d father %d `date` >> omg.log", status->pid, father);
	system(tmp8);

		wait(&father);


	char *tmp9 = NULL;
	ft_sprintf(&tmp9, "echo finished pid %d father %d `date` >> omg.log", status->pid, father);
	system(tmp9);

		// remove finished multi proc
//		t_status *tmp = status->next;
//		ft_init_status(status);
//		status->next = tmp;

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

void	ft_exec_job(t_tm *tm, int id_job)
{
	ft_printf("executing: [%s]\n", tm->jobs[id_job].name);
	pid_t       father;
    t_status    *status;
	int			i;

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
			//	else
			//		restart

			}
			exit(0);
		}		
	//	if (father > 0)
	//	{
	//		ft_printf("1st process id: [%d]\n", father);
	//	}
		status = status->next;
	}
	
}

/*
void	ft_exec_job(t_tm *tm, int id_job)
{
	ft_printf("executing: [%s]\n", tm->jobs[id_job].name);
	pid_t       father;
    t_status    *status;
	int			i;

	status = &tm->shared->status[id_job];
	i = -1;
	while (++i < tm->jobs[id_job].nb_procs && status)
	{
		father = fork();
		if (!father)
		{
			father = fork();
			if (!father)
			{
	//			status->state = starting;
			//	status->started_time = time(NULL);
				ft_sleep(tm->jobs[id_job].start_time);

				char *tmp = NULL;
				ft_sprintf(&tmp, "echo pid %d >> lol.log", status->pid);
				system(tmp);

	//			if (status->pid > 0 && kill(status->pid, 0) > -1)
	//				status->state = running;
				status->state = running;
			//	else
			//		restart
//				exit(0);
			}
			else
			{
				ft_exec_job_inner(tm, id_job, status);
//				exit(0);
			}
//			ft_sleep(4);
			exit(0);
		}	
	//	if (father > 0)
	//	{
	//		ft_printf("1st process id: [%d]\n", father);
	//	}
		else
			status = status->next;
	}
	
}*/
/*
void	ft_exec_job(t_tm *tm, int id_job)
{
	ft_printf("executing: [%s]\n", tm->jobs[id_job].name);
	pid_t       father;
    t_status    *status;
	int			i;

 //   status = ft_get_last_status(&tm->shared->status[id_job]);
	status = &tm->shared->status[id_job];
//	ft_init_status(&tm->shared->status[id_job]);
//    ft_init_status(status);
	i = -1;
	while (++i < tm->jobs[id_job].nb_procs && status)
	{
		father = fork();
		if (!father)
			ft_exec_job_inner(tm, id_job, status);
		if (father > 0)
		{
		//	tm->shared->status[id_job].pid = father;
		//	ft_printf("process id: [%d]\n", father);
		//	tm->shared->status[id_job].started_time = time(NULL);
		//	tm->shared->status[id_job].state = running;
	//        status->pid = father;
			ft_printf("1st process id: [%d]\n", father);
	//		status->started_time = time(NULL);
	//		status->state = running;
			status = status->next;
		}
	}
	
}*/
