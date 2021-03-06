/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 05:53:34 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 05:53:34 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster.h"

static void	ft_parse_token2(t_tm *tm, char *token, char *value, int current_job)
{
	if (!ft_strcmp(token, "umask"))
		ft_strcpy(tm->jobs[current_job].umask, value);
	else if (!ft_strcmp(token, "workingdir"))
		ft_strcpy(tm->jobs[current_job].working_dir, value);
	else if (!ft_strcmp(token, "autostart"))
		tm->jobs[current_job].autostart = ft_atoi(value);
	else if (!ft_strcmp(token, "autorestart"))
		tm->jobs[current_job].autorestart = ft_atoi(value);
	else if (!ft_strcmp(token, "exitcodes"))
		ft_append_int_val(tm->jobs[current_job].exit_codes, ft_atoi(value));
	else if (!ft_strcmp(token, "startretries"))
		tm->jobs[current_job].start_retries = ft_atoi(value);
	else if (!ft_strcmp(token, "starttime"))
		tm->jobs[current_job].start_time = ft_atoi(value);
	else if (!ft_strcmp(token, "stoptime"))
		tm->jobs[current_job].stop_time = ft_atoi(value);
	else if (!ft_strcmp(token, "stopsignal") && ft_atoi(value) > 0)
		tm->jobs[current_job].stop_signal = ft_atoi(value);
	else if (!ft_strcmp(token, "stdout"))
		ft_strcpy(tm->jobs[current_job].stdout, value);
	else if (!ft_strcmp(token, "stderr"))
		ft_strcpy(tm->jobs[current_job].stderr, value);
	else
		ft_printf("Unknown token: [%s] or bad value: [%s]\n", token, value);
}

static void	ft_parse_token(t_tm *tm, char *token, char *value, int current_job)
{
	int			i;
	t_status	*tmp;

	if (!ft_strcmp(token, "name"))
		ft_strcpy(tm->jobs[current_job].name, value);
	else if (!ft_strcmp(token, "cmd"))
		ft_strcpy(tm->jobs[current_job].cmd, value);
	else if (!ft_strcmp(token, "numprocs"))
	{
		tm->jobs[current_job].nb_procs = ft_atoi(value);
		if (ft_atoi(value) > 0)
		{
			i = 0;
			tmp = &tm->shared->status[current_job];
			ft_init_status(tmp);
			while (++i < ft_atoi(value))
			{
				tmp->next = ft_shared_malloc(sizeof(t_status));
				tmp = tmp->next;
				ft_init_status(tmp);
			}
		}
	}
	else
		ft_parse_token2(tm, token, value, current_job);
}

static void	ft_parse_next_token(t_tm *tm, char *line, int current_job)
{
	char	*token;

	token = NULL;
	if (ft_strlen(line) > 1 && line[0] == '-')
		ft_append_int_val(tm->jobs[current_job].exit_codes, ft_atoi(line + 1));
	else if (ft_strlen(line) > 1 && line[0] == '_' && ft_strchr(line, ':'))
	{
		ft_sprintf(&token, "%.*s", ft_strchr(line, ':') - line - 1, line + 1);
		if (ft_strlen(line) > (ft_strlen(token) + 3))
			ft_append_env(&tm->jobs[current_job], token,
					line + ft_strlen(token) + 3);
	}
	else if (ft_strchr(line, ':'))
	{
		ft_sprintf(&token, "%.*s", ft_strchr(line, ':') - line, line);
		if (ft_strlen(line) > (size_t)((ft_strchr(line, ':') - line) + 2))
			ft_parse_token(tm, token, line + (ft_strchr(line, ':') - line) + 2,
					current_job);
		else if (ft_strcmp(line, "exitcodes:") && ft_strcmp(line, "env:"))
			ft_printf("bad token: [%s]\n", token);
	}
	free(token);
}

void		ft_parse_config(t_tm *tm)
{
	int		fd;
	char	*line;
	int		empty_line;

	line = NULL;
	empty_line = 0;
	tm->jobs_cnt = 0;
	ft_init_job(tm, &tm->jobs[tm->jobs_cnt]);
	fd = open(tm->config, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (line && !line[0])
			empty_line = 1;
		else if (line[0] != '#')
		{
			if (empty_line && tm->jobs[tm->jobs_cnt].name[0])
				ft_init_job(tm, &tm->jobs[++tm->jobs_cnt]);
			ft_parse_next_token(tm, line, tm->jobs_cnt);
			empty_line = 0;
		}
		free(line);
	}
	free(line);
	close(fd);
	tm->jobs[0].name[0] ? tm->jobs_cnt++ : 0;
}
