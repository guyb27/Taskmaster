/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_commands.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2060/00/00 18:14:45 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/23 23:03:07 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "taskmaster.h"

char			*ft_get_logo(void)
{
	char		*ret;

	ret = NULL;
	ft_sprintf(&ret,
	"\033[94m _            _                        _ \n"
	"| |          | |                      | |           \n"
	"| |_ __ _ ___| | ___ __ ___   __ _ ___| |_ ___ _ __ \n"
	"| __/ _` / __| |/ / '_ ` _ \\ / _` / __| __/ _ \\ '__|\n"
	"| || (_| \\__ \\   <| | | | | | (_| \\__ \\ ||  __/ |   \n"
	" \\__\\__,_|___/_|\\_\\_| |_| |_|\\__,_|___/\\__\\___|_|\n\n\n\033[0;m");
	return (ret);
}

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

size_t			ft_tablen(char **tab)
{
	size_t	i;

	i = -1;
	while (tab[++i])
		;
	return (i);
}

void			ft_init_job(t_tm *tm, t_job *job)
{
	size_t i;

	i = -1;
	ft_bzero(job->name, sizeof(job->name));
	ft_bzero(job->cmd, sizeof(job->cmd));
	job->nb_procs = 0;
	ft_bzero((char*)job->umask, 5);
	ft_bzero(job->working_dir, sizeof(job->working_dir));
	job->autostart = 0;
	job->autorestart = 0;
	while (++i < sizeof(job->exit_codes) / sizeof(int))
		job->exit_codes[i] = -42;
	job->start_retries = 0;
	job->start_time = 0;
	job->stop_time = 0;
	job->stop_signal = 3;
	ft_bzero(job->stdout, sizeof(job->stdout));
	ft_bzero(job->stderr, sizeof(job->stderr));
	job->env = ft_tabdup(tm->env);
}
