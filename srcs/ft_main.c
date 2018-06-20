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

typedef struct		s_keyval
{
	char			*key;
	char			*value;
	struct s_keyval	*next;
}					t_keyval;

typedef struct		s_job
{
	char			name[1000];
	char			cmd[1000];
	int				nb_procs;
	char			umask[5];
	char			working_dir[1000];
	int				autostart;
	int				autorestart;
	int				exit_codes[10];
	int				start_retries;
	int				start_time;
	int				stop_time;
	char			stop_signal[10];
	char			stdout[1000];
	char			stderr[1000];
	t_keyval		*env;
}					t_job;

typedef struct		s_status
{
	int				started_time;
	int				stopped_time;
}					t_status;

typedef struct		s_tm
{
	t_job			jobs[1000];
	t_status		status[1000];
	int				jobs_cnt;
	char			**env;
}					t_tm;

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
	ft_bzero(job->stop_signal, 10);
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
	ft_printf("stopsignal:\t'%s'\n", tm->jobs[job_id].stop_signal);
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

void	ft_append_int_val(int list[], int val)
{
	int	i;

	i = 0;
	while (list[i] > -42)
		i++;
	list[i] = val;
}

void	ft_append_env(t_job *job, char *key, char *value)
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

void	ft_parse_token(t_tm *tm, char *token, char *value, int current_job)
{
	if (!ft_strcmp(token, "name"))
		ft_strcpy(tm->jobs[current_job].name, value);
	else if (!ft_strcmp(token, "cmd"))
		ft_strcpy(tm->jobs[current_job].cmd, value);
	else if (!ft_strcmp(token, "numprocs"))
		tm->jobs[current_job].nb_procs = ft_atoi(value);
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
	else if (!ft_strcmp(token, "stopsignal"))
		ft_strcpy(tm->jobs[current_job].stop_signal, value);
	else if (!ft_strcmp(token, "stdout"))
		ft_strcpy(tm->jobs[current_job].stdout, value);
	else if (!ft_strcmp(token, "stderr"))
		ft_strcpy(tm->jobs[current_job].stderr, value);
	else
		ft_printf("Unknown token: [%s]\n", token);
}

void	ft_parse_next_token(t_tm *tm, char *line, int current_job)
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
	
	current_job = 0;
	ft_init_job(&tm->jobs[current_job]);
	fd = open(config_file, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		if (line && !line[0])
			ft_init_job(&tm->jobs[++current_job]);
		else
			ft_parse_next_token(tm, line, current_job);
		free(line);
	}
	free(line);
	close(fd);
	tm->jobs_cnt = current_job + 1;
}

//------------------------------------------------------------------------------
void	ft_init_status(t_status *status)
{
	status->started_time = 0;
	status->stopped_time = 0;
}

void	ft_exec_job(t_tm *tm, int id_job)
{
	pid_t pid;

	ft_init_status(&tm->status[id_job]);
	pid = fork();
	if (!pid)
	{
		ft_printf("Starting program: [%s]\n", tm->jobs[id_job].name);
		char *args[3] = { "ls", "-l", NULL };
		execve("/bin/ls", args, tm->env);
		tm->status[id_job].started_time = time(NULL);
		ft_printf("on dirait que lexec a merdée");
	}
	if (pid > 0)
		wait(&pid);
}

void	ft_exec_all_jobs(t_tm *tm)
{
	int i;

	i = -1;
	while (++i < tm->jobs_cnt)
		ft_exec_job(tm, i);
}

int		main(int argc, char *argv[], char *env[])
{
	t_tm	tm;

	tm.env = env;
	tm.jobs_cnt = 0;
	if (argc == 2)
	{
		ft_parse_config(&tm, argv[1]);
		for (int i = 0; i < tm.jobs_cnt; i++)
			ft_debug_job(&tm, i);
		ft_exec_all_jobs(&tm);
	}
	else
		ft_printf("usage: taskmaster config_file\n");
	return (0);
}
