/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_main.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/15 18:14:45 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/23 23:36:33 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "taskmaster.h"

static void	ft_reload(t_tm *tm)
{
	ft_cmd_stop(tm, "all");
	ft_free_jobs(tm);
	ft_parse_config(tm);
	ft_autostart_jobs(tm);
	ft_strdel(&tm->ret);
	tm->ret = ft_cmd_help(tm);
	ft_printf("Config file reloaded\n");
}

void		ft_process_cmd(t_tm *tm)
{
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
	else if (!ft_strcmp(tm->cmd, "json status"))
		ft_send_json_status(tm);
	else if (!strcmp(tm->cmd, "reload"))
		ft_reload(tm);
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

void		ft_taskmaster(int argc, char *argv[], char *env[])
{
	t_tm		tm;

	ft_bzero(&tm, sizeof(t_tm));
	tm.argv = argv;
	tm.shared = ft_megamalloc(sizeof(t_shared));
	tm.env = env;
	tm.jobs_cnt = 0;
	ft_strcpy(tm.config, argv[1]);
	ft_parse_config(&tm);
	ft_autostart_jobs(&tm);
	if (argc > 2)
	{
		tm.server = ft_init_server(argv[2],
				argc > 3 ? ft_atoi(argv[3]) : SERVER_PORT);
		ft_server_loop(&tm.server, &tm);
	}
	else
		while (1)
		{
			ft_get_user_input(&tm);
			ft_process_cmd(&tm);
			ft_printf("%s", tm.ret);
		}
	ft_quit(&tm);
}

int			main(int argc, char *argv[], char *env[])
{
	signal(SIGCHLD, SIG_IGN);
	if (argc > 1 && access(argv[1], F_OK) > -1)
		ft_taskmaster(argc, argv, env);
	else if (argc > 1 && access(argv[1], F_OK) == -1)
		ft_printf("error: not a valid config file\n");
	else
		ft_printf("usage: taskmaster config_file [ip] [port]\n");
	return (0);
}
