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
	t_status	*tmp;
	t_status	*tmp_2;
	int			i;
	int			j;

	i = -1;
	while (++i < tm->jobs_cnt)
	{
		ft_tabdel(&tm->jobs[i].env);
		tmp = &tm->shared->status[i];
		j = 0;
		while (tmp)
		{
			tmp_2 = tmp;
			tmp = tmp->next;
			if (j++ > 0)
				ft_megafree(tmp_2, sizeof(t_status));
		}
	}
}

void		ft_quit(t_tm *tm)
{
	ft_printf("Quitting taskmaster\n");
	ft_free_jobs(tm);
	ft_megafree(tm->shared, sizeof(t_shared));
	exit(0);
}

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
}

void		ft_get_user_input(t_tm *tm)
{
	if (tm->cmd)
		free(tm->cmd);
	ft_printf("$> ");
	get_next_line(0, &tm->cmd);
}

int			main(int argc, char *argv[], char *env[])
{
	t_tm	tm;

	tm.argv = argv;
	signal(SIGCHLD, SIG_IGN);
	tm.shared = ft_megamalloc(sizeof(t_shared));
	tm.env = env;
	tm.jobs_cnt = 0;
	if (argc == 2 && access(argv[1], F_OK) > -1)
	{
		ft_strcpy(tm.config, argv[1]);
		ft_parse_config(&tm);
//		for (int i = 0; i < tm.jobs_cnt; i++)
//			ft_debug_job(&tm, i);
		ft_autostart_jobs(&tm);
		while (1)
		{
			ft_get_user_input(&tm);
			ft_process_cmd(&tm);
		}
	}
	else if (argc == 2 && access(argv[1], F_OK) == -1)
		ft_printf("error: not a valid config file\n");
	else
		ft_printf("usage: taskmaster config_file\n");
	munmap(tm.shared, sizeof(t_shared));
	return (0);
}
