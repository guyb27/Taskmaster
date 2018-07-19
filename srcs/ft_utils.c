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

void		*ft_megamalloc(int size)
{
	void *var;
	
	var = mmap(NULL, size, 
				PROT_READ|PROT_WRITE, 
				MAP_SHARED|MAP_ANONYMOUS, -1, 0);
	return (var);
}

void		ft_megafree(void *var, int size)
{
	munmap(var, size);
}

t_status    *ft_get_last_status(t_status *list)
{
    t_status *tmp;

    tmp = list;
    while (tmp->next)
        tmp = tmp->next;
    return (tmp);
}

void	ft_init_job(t_job *job)
{
	int i;

	i = -1;
	ft_bzero(job->cmd, 1000);
	job->nb_procs = 0;
	ft_bzero((char*)job->umask, 5);
	ft_bzero(job->working_dir, 1000);
	job->autostart = 0;
	job->autorestart = 0;
	while (++i < 3)
		job->exit_codes[i] = -42;
	job->start_retries = 0;
	job->start_time = 0;
	job->stop_time = 0;
	job->stop_signal = 3;
//	ft_bzero(job->stop_signal, 10);
	ft_bzero(job->stdout, 1000);
	ft_bzero(job->stderr, 1000);
	job->env = NULL;
}

void	ft_debug_job(t_tm *tm, int job_id)
{
	ft_printf("\n==> Debugging job id [%d]\n", job_id);
	ft_printf("\e[38;5;208m");
	ft_printf("name:\t\t'%s'\n", tm->jobs[job_id].name);
	ft_printf("cmd:\t\t'%s'\n", tm->jobs[job_id].cmd);
	ft_printf("nb_procs:\t[%d]\n", tm->jobs[job_id].nb_procs);
	ft_printf("umask:\t\t'%s'\n", tm->jobs[job_id].umask);
	ft_printf("workingdir:\t'%s'\n", tm->jobs[job_id].working_dir);
	ft_printf("autostart:\t[%d]\n", tm->jobs[job_id].autostart);
	ft_printf("autorestart:\t[%d]\n", tm->jobs[job_id].autorestart);
	ft_printf("startretries:\t[%d]\n", tm->jobs[job_id].start_retries);
	ft_printf("starttime:\t[%d]\n", tm->jobs[job_id].start_time);
	ft_printf("stoptime:\t[%d]\n", tm->jobs[job_id].stop_time);
	ft_printf("stopsignal:\t[%d]\n", tm->jobs[job_id].stop_signal);
	ft_printf("stdout:\t\t'%s'\n", tm->jobs[job_id].stdout);
	ft_printf("stderr:\t\t'%s'\n", tm->jobs[job_id].stderr);
	ft_printf("exitcodes:\t");
	for (int i = 0; tm->jobs[job_id].exit_codes[i] != -42; i++)
		ft_printf("[%d] ", tm->jobs[job_id].exit_codes[i]);
	ft_printf("\n");
	ft_printf("env:\n");
	for (t_keyval *tmp = tm->jobs[job_id].env; tmp; tmp = tmp->next)
		ft_printf("\t\t'%s' => '%s'\n", tmp->key, tmp->value);
	ft_printf("{eoc}");
}