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

void	ft_autostart_jobs(t_tm *tm)
{
	int i;

	i = -1;
	while (++i < tm->jobs_cnt)
	{
		if (tm->jobs[i].autostart == 1)
			ft_exec_job(tm, i, 0);
	}
}

void	ft_process_cmd(t_tm *tm)
{
	if (!strncmp(tm->cmd, "start", 5) && (ft_strlen(tm->cmd) > 6))
		ft_cmd_start(tm, tm->cmd + 6);
	else if (!strncmp(tm->cmd, "restart", 7) && (ft_strlen(tm->cmd) > 8))
		ft_cmd_restart(tm, tm->cmd + 8);
	else if (!strncmp(tm->cmd, "stop", 4) && (ft_strlen(tm->cmd) > 5))
		ft_cmd_stop(tm, tm->cmd + 5);
	else if (!strncmp(tm->cmd, "status", 6) && (ft_strlen(tm->cmd) > 7))
		ft_cmd_status(tm, tm->cmd + 7);
	else if (!strcmp(tm->cmd, "reload"))
		ft_printf("reloading config file\n");
	else if (!strcmp(tm->cmd, "shutdown"))
	{
		ft_printf("Quitting taskmaster\n");
		exit(0);
	}
	else if (!ft_strcmp(tm->cmd, "exit"))
		exit(0);
}

/*
**------------------------------------------------------------------------------
*/

void	ft_get_user_input(t_tm *tm)
{
	if (tm->cmd)
		free(tm->cmd);
	ft_printf("$> ");
	get_next_line(0, &tm->cmd);
}

int		main(int argc, char *argv[], char *env[])
{
	t_tm	tm;

	tm.argv = argv;
	signal(SIGCHLD, SIG_IGN);
	tm.shared = ft_megamalloc(sizeof(t_shared));
	tm.env = env;
	tm.jobs_cnt = 0;
	if (argc == 2)
	{
		ft_parse_config(&tm, argv[1]);
		for (int i = 0; i < tm.jobs_cnt; i++)
			ft_debug_job(&tm, i);
		ft_autostart_jobs(&tm);
		while (1)
		{
			ft_get_user_input(&tm);
		ft_printf("{blue}cmd: [%s]{eoc}\n", tm.cmd);
			ft_process_cmd(&tm);
		}
	}
	else
		ft_printf("usage: taskmaster config_file\n");
	munmap(tm.shared, sizeof(t_shared));
	return (0);
}
