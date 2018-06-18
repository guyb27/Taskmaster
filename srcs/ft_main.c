/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_main.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/15 18:14:45 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2018/03/15 18:17:48 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "taskmaster.h"
#include "cJSON.h"

typedef struct	s_job
{
	char		name[1000];
	char		cmd[1000];
	int			nb_procs;
	char		umask[3];
	char		workind_dir[1000];
	int			autostart;
	int			autorestart;
	int			exit_codes[10];
	int			start_retries;
	int			start_time;
	int			stop_time;
	char		stdout[1000];
	char		stderr[1000];
	char		**env;
}				t_job;

typedef struct	s_tm
{
	t_job		jobs[1000];
}				t_tm;

void	ft_init_job(t_job *job)
{
	ft_bzero(job->cmd, 1000);
	job->nb_procs = 0;
	ft_bzero((char*)job->umask, 3);
	ft_bzero(job->workind_dir, 1000);
	job->autostart = 0;
	job->autorestart = 0;
	ft_strchr((char*)job->exit_codes, -42);
	job->start_retries = 0;
	job->start_time = 0;
	job->stop_time = 0;
	ft_bzero(job->stdout, 1000);
	ft_bzero(job->stderr, 1000);
	job->env = NULL;
}

void	ft_parse_line(t_tm *tm, char *line)
{
	(void)tm;
	ft_printf("line: [%r]\n", line);
//	if (!ft_strncmp(line, "    "))
}

void	ft_parse_config(t_tm *tm, char *config_file)
{
	int		fd;
	char	*line;
	char	*token;

	
	fd = open(config_file, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		ft_sprintf(&token, "%.*s", ft_strchr(line, ':') - line, line);
		ft_printf("token: [%s], value: [%s]\n", token, line - ft_strchr(line, ':'));
		if (ft_strlen(line) > 5)
		{
			ft_parse_line(tm, line);
		}
		free(line);
	}
	free(line);
	close(fd);
}
/*
void	ft_parse_config(t_tm *tm, char *config_file)
{
	int		fd;
	char	content[100000];
	cJSON	*json;

(void)tm;
	fd = open(config_file, O_RDONLY);
	read(fd, content, 100000);
//	ft_printf("content: [%r]\n", content);
	json = cJSON_Parse(content);

	ft_printf("VOILA: [%s]\n", cJSON_Print(json));

	cJSON_Delete(json);
}*/

int		main(int argc, char *argv[])
{
	t_tm	tm;

	if (argc == 2)
	{
		ft_parse_config(&tm, argv[1]);
	}
	else
		ft_printf("usage: taskmaster config_file\n");
	return (0);
}
