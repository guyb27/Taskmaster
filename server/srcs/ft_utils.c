/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_commands.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2060/00/00 18:14:45 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/16 06:07:23 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "taskmaster.h"

void			ft_perror(char *msg)
{
	if (msg)
		ft_printf("%s: ", msg);
	if (errno <= sys_nerr - 1)
		ft_printf("%s\n", sys_errlist[errno]);
	else
		ft_printf("Unknown error: %d\n", errno);
}

unsigned int	ft_sleep(unsigned int seconds)
{
	struct timespec ts;

	ts.tv_sec = seconds;
	ts.tv_nsec = 0;
	if (nanosleep(&ts, &ts) == 0)
		return (0);
	return (ts.tv_sec);
}

void			*ft_megamalloc(int size)
{
	void *var;

	var = mmap(NULL, size,
				PROT_READ | PROT_WRITE,
				MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	return (var);
}

void			ft_megafree(void *var, int size)
{
	munmap(var, size);
}

void			ft_init_job(t_job *job)
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
	ft_bzero(job->stdout, 1000);
	ft_bzero(job->stderr, 1000);
	job->env = NULL;
}
