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

void		ft_free_jobs(t_tm *tm)
{
	int			i;

	i = -1;
	while (++i < tm->jobs_cnt)
	{
		ft_tabdel(&tm->jobs[i].env);
	}
	tm->jobs_cnt = 0;
}

void		ft_quit(t_tm *tm)
{
	ft_printf("Quitting taskmaster\n");
	ft_free_jobs(tm);
	ft_megafree(tm->shared, sizeof(t_shared));
	ft_strdel(&tm->ret);
	// close sockets etc...
	exit(0);
}
/*
void		ft_process_cmd(t_tm *tm)
{
	if (!strncmp(tm->cmd, "start", 5) && (ft_strlen(tm->cmd) > 6))
		ft_cmd_start(tm, tm->cmd + 6);
	else if (!strncmp(tm->cmd, "restart", 7) && (ft_strlen(tm->cmd) > 8))
		ft_cmd_restart(tm, tm->cmd + 8);
	else if (!strncmp(tm->cmd, "stop", 4) && (ft_strlen(tm->cmd) > 5))
		ft_cmd_stop(tm, tm->cmd + 5);
	else if (!strncmp(tm->cmd, "pause", 5) && (ft_strlen(tm->cmd) > 6))
		ft_cmd_pause(tm, tm->cmd + 6);
	else if (!strncmp(tm->cmd, "status", 6) && (ft_strlen(tm->cmd) > 7))
		ft_cmd_status(tm, tm->cmd + 7);
	else if (!strcmp(tm->cmd, "reload"))
	{
		ft_free_jobs(tm);
		ft_parse_config(tm);
	//	ft_autostart_jobs(tm); maybe a bad idea
		ft_printf("Config file reloaded\n");
	}
	else if (!strcmp(tm->cmd, "shutdown"))
	{
		ft_cmd_stop(tm, "all");
		ft_quit(tm);
	}
	else if (!ft_strcmp(tm->cmd, "exit"))
		ft_quit(tm);
} */

void		ft_send_json_status(t_tm *tm)
{
	t_status	*st;
	char		**json;
	int			i;

	json = &tm->ret;
	ft_sprintf(json, "[\n");
	i = -1;
	while (++i < tm->jobs_cnt)
	{
		st = &tm->shared->status[i];
		ft_sprintf(json, "%s{\n\"name\": \"%s\",\n", *json, tm->jobs[i].name);
		ft_sprintf(json, "%s\"status\": \"%d\",\n", *json, st->state);
		ft_sprintf(json, "%s\"retries\": \"%d\",\n", *json, st->retries);
		ft_sprintf(json, "%s\"pid\": \"%d\",\n", *json, st->pid);
		ft_sprintf(json, "%s\"timetype\": \"%s\",\n", *json,
						st->state == running ? "starttime" : "downtime");
		if (st->state > stopped && st->state < error)
			ft_sprintf(json, "%s\"elapsed\": \"%zu\"\n", *json,
												time(NULL) - st->started_time);
		else
			ft_sprintf(json, "%s\"elapsed\": \"%zu\"\n", *json,
						st->stopped_time ? time(NULL) - st->stopped_time : 0);
		ft_sprintf(json, "%s}%s\n", *json, i + 1 < tm->jobs_cnt ? "," : "");
	}
	ft_sprintf(json, "%s]\n", *json);
}

char		*ft_cmd_help(t_tm *tm)
{
	int		i;
	char	*ret;

	ret = NULL;
	i = 0;
	ft_sprintf(&ret, "Synopsis: command [process | all]\n");
	ft_sprintf(&ret, "%scommand list:\n", ret);
	ft_sprintf(&ret, "%s\tstart [process | all]\n", ret);
	ft_sprintf(&ret, "%s\trestart [process | all]\n", ret);
	ft_sprintf(&ret, "%s\tstop [process | all]\n", ret);
	ft_sprintf(&ret, "%s\tpause [process | all]\n", ret);
	ft_sprintf(&ret, "%s\tstatus [process | all]\n", ret);
	ft_sprintf(&ret, "%s\treload\n", ret);
	ft_sprintf(&ret, "%s\tshutdown\n", ret);
	ft_sprintf(&ret, "%s\texit\n", ret);
	ft_sprintf(&ret, "%sprocess list:\n", ret);
	while (i < tm->jobs_cnt)
		ft_sprintf(&ret, "%s\t%s\n", ret, tm->jobs[i++].name);
	return (ret);
}

void		ft_process_cmd(t_tm *tm)
{
	printf("CMD: [%s]\n", tm->cmd);
	if (!ft_strncmp(tm->cmd, "start", 5) && (ft_strlen(tm->cmd) > 6))
		ft_cmd_start(tm, tm->cmd + 6);
	else if (!ft_strncmp(tm->cmd, "restart", 7) && (ft_strlen(tm->cmd) > 8))
		ft_cmd_restart(tm, tm->cmd + 8);
	else if (!ft_strncmp(tm->cmd, "stop", 4) && (ft_strlen(tm->cmd) > 5))
		ft_cmd_stop(tm, tm->cmd + 5);
	else if (!ft_strncmp(tm->cmd, "pause", 5) && (ft_strlen(tm->cmd) > 6))
		ft_cmd_pause(tm, tm->cmd + 6);
	else if (!ft_strncmp(tm->cmd, "status", 6) && (ft_strlen(tm->cmd) > 7))
		ft_cmd_status(tm, tm->cmd + 7);
/*	else if (!ft_strcmp(tm->cmd, "reload"))
		ft_printf("reloading config file (not yet implemented..)\n");
	else if (!ft_strcmp(tm->cmd, "shutdown"))
	{
		ft_printf("Quitting taskmaster\n");
		exit(0);
	}
	else if (!ft_strcmp(tm->cmd, "json status"))
		ft_send_json_status(tm);
	else if (!ft_strcmp(tm->cmd, "exit"))
	{
		//Ne pas oublier de close la socket
		ft_shutdown(tm, server);
	} */
	else if (!ft_strcmp(tm->cmd, "json status"))
		ft_send_json_status(tm);
	else if (!strcmp(tm->cmd, "reload"))
	{
		ft_cmd_stop(tm, "all");
		ft_free_jobs(tm);
	//	ft_printf("job count: [%d]\n", tm->jobs_cnt);
		ft_parse_config(tm);
	//	ft_printf("job count: [%d]\n", tm->jobs_cnt);
	//	for (int i = 0; i < tm->jobs_cnt; i++)
	//		ft_debug_job(tm, i);
		ft_autostart_jobs(tm);
		ft_printf("Config file reloaded\n");
	}
	else if (!strcmp(tm->cmd, "shutdown"))
	{
		ft_cmd_stop(tm, "all");
		ft_quit(tm);
	}
	else if (!ft_strcmp(tm->cmd, "exit"))
		ft_quit(tm);
	else if (!ft_strcmp(tm->cmd, "help"))
		tm->ret = ft_cmd_help(tm);
	else
		ft_sprintf(&tm->ret, "[%s]: Command not found\n", tm->cmd);
}

void		ft_get_user_input(t_tm *tm)
{
	char *cmd;

	cmd = NULL;
	ft_printf("$> ");
	get_next_line(0, &cmd);
	ft_strcpy(tm->cmd, cmd);
	free(cmd);
}

int			main(int argc, char *argv[], char *env[])
{
	t_tm		tm;

	ft_bzero(&tm, sizeof(t_tm));
	tm.argv = argv;
	signal(SIGCHLD, SIG_IGN);
	tm.shared = ft_megamalloc(sizeof(t_shared));
	tm.env = env;
	tm.jobs_cnt = 0;
	if (argc > 1 && access(argv[1], F_OK) > -1)
	{
		ft_strcpy(tm.config, argv[1]);
		ft_parse_config(&tm);
		ft_autostart_jobs(&tm);
//		for (int i = 0; i < tm.jobs_cnt; i++)
//			ft_debug_job(&tm, i);
		if (argc > 2)
		{
			tm.server = ft_init_server(argv[2],
									argc > 3 ? ft_atoi(argv[3]) : SERVER_PORT);
			ft_server_loop(&tm.server, &tm);
		}
		else
		{
			while (1)
			{
				ft_get_user_input(&tm);
				ft_process_cmd(&tm);
				ft_printf("%s", tm.ret);
			}
		}
	}
	else if (argc > 1 && access(argv[1], F_OK) == -1)
		ft_printf("error: not a valid config file\n");
	else
	{
		ft_printf("usage: taskmaster config_file [ip] [port]\n");
	}
//	munmap(tm.shared, sizeof(t_shared));
//	return (0);
	ft_quit(&tm);
}
