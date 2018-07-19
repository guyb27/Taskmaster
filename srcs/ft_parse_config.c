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

static void	ft_append_int_val(int list[], int val)
{
	int	i;

	i = 0;
	while (list[i] > -42)
		i++;
	list[i] = val;
}

static void	ft_append_env(t_job *job, char *key, char *value)
{
	t_keyval *new;
	t_keyval *tmp;

	tmp = job->env;
	while (tmp && tmp->next)
		tmp = tmp->next;
	new = (t_keyval*)malloc(sizeof(t_keyval));
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (!tmp)
		job->env = new;
	else
		tmp->next = new;
}

static void	ft_parse_token(t_tm *tm, char *token, char *value, int current_job)
{
	if (!ft_strcmp(token, "name"))
		ft_strcpy(tm->jobs[current_job].name, value);
	else if (!ft_strcmp(token, "cmd"))
		ft_strcpy(tm->jobs[current_job].cmd, value);
	else if (!ft_strcmp(token, "numprocs"))
	{
		tm->jobs[current_job].nb_procs = ft_atoi(value);
		// malloc chained list elements needed for multi procs
		if (ft_atoi(value) > 0)
		{
			int i = 0;
			t_status *tmp = &tm->shared->status[current_job];
			while (++i < ft_atoi(value))
			{
				tmp->next = ft_megamalloc(sizeof(t_status));
				tmp = tmp->next;
			}
		}
	}
	else if (!ft_strcmp(token, "umask"))
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
	//	ft_strcpy(tm->jobs[current_job].stop_signal, value);
	else if (!ft_strcmp(token, "stdout"))
		ft_strcpy(tm->jobs[current_job].stdout, value);
	else if (!ft_strcmp(token, "stderr"))
		ft_strcpy(tm->jobs[current_job].stderr, value);
	else
		ft_printf("Unknown token: [%s]\n", token);
}

static void	ft_parse_next_token(t_tm *tm, char *line, int current_job)
{
	char	*token;

	token = NULL;
	if (ft_strlen(line) > 1 && line[0] == '-')
		ft_append_int_val(tm->jobs[current_job].exit_codes, ft_atoi(line + 1));
	else if (ft_strlen(line) > 1 && line[0] == '_' && ft_strchr(line, ':'))
	{
	//	ft_printf("add key -> value to env\n");
		ft_sprintf(&token, "%.*s", ft_strchr(line, ':') - line - 1, line + 1);
		if (ft_strlen(line) > (ft_strlen(token) + 3))
			ft_append_env(&tm->jobs[current_job], token, line + ft_strlen(token) + 3);
	//	ft_printf("adding key: [%s], value: [%s]\n", token, line + ft_strlen(token) + 3);
	}
	else if (ft_strchr(line, ':'))
	{
		ft_sprintf(&token, "%.*s", ft_strchr(line, ':') - line, line);
		if (ft_strlen(line) > (size_t)((ft_strchr(line, ':') - line) + 2))
			ft_parse_token(tm, token, line + (ft_strchr(line, ':') - line) + 2, current_job);
	//		ft_printf("token: [%s], value: [%s]\n", token, line + (ft_strchr(line, ':') - line) + 2);
		else
			ft_printf("bad token: [%s]\n", token);
	}	
}

void	ft_parse_config(t_tm *tm, char *config_file)
{
	int		fd;
	char	*line;
	int		current_job;
	int		empty_line;
	
	empty_line = 0;
	current_job = 0;
	ft_init_job(&tm->jobs[current_job]);
	fd = open(config_file, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		if (line && !line[0])
			empty_line = 1;
		else if (line[0] != '#')
		{
			if (empty_line && tm->jobs[current_job].name[0])
				ft_init_job(&tm->jobs[++current_job]);
			ft_parse_next_token(tm, line, current_job);
			empty_line = 0;
		}
		free(line);
	}
	free(line);
	close(fd);
	tm->jobs_cnt = current_job + 1;
}