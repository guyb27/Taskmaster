/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_main.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/15 18:14:45 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/06 01:48:32 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "taskmaster.h"

static void	ft_free_env(t_keyval *env)
{
	t_keyval	*env_2;

	while (env)
	{
		env_2 = env;
		env = env->next;
		free(env_2->key);
		free(env_2->value);
		free(env_2);
	}
}

void		ft_shutdown(t_tm *tm)
{
	t_status	*tmp;
	t_status	*tmp_2;
	int			i;
	int			j;

	i = -1;
	while (++i < tm->jobs_cnt)
	{
		ft_free_env(tm->jobs[i].env);
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
	ft_megafree(tm->shared, sizeof(t_shared));
	exit(0);
}

void		ft_process_cmd(t_tm *tm)
{
	printf("CMD: [%s]\n", tm->cmd);
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
		ft_printf("reloading config file (not yet implemented..)\n");
	else if (!strcmp(tm->cmd, "shutdown"))
	{
		ft_printf("Quitting taskmaster\n");
		exit(0);
	}
	else if (!ft_strcmp(tm->cmd, "exit"))
		ft_shutdown(tm);
	else
		ft_sprintf(&tm->ret, "[%s]: Command not found\n", tm->cmd);
}

int			main(int argc, char *argv[], char *env[])
{
	t_tm		tm;
	t_server	server;

	ft_bzero(&tm, sizeof(t_tm));
	tm.argv = argv;
	signal(SIGCHLD, SIG_IGN);
	tm.shared = ft_megamalloc(sizeof(t_shared));
	tm.env = env;
	tm.jobs_cnt = 0;
	if (argc == 2 && access(argv[1], F_OK) > -1)
	{
		ft_parse_config(&tm, argv[1]);
		ft_autostart_jobs(&tm);
		server = ft_init_server(SERVER_PORT);
		ft_server_loop(&server, &tm);
	}
	else if (access(argv[1], F_OK) == -1)
		ft_printf("error: not a valid config file\n");
	else
		ft_printf("usage: taskmaster config_file\n");
	munmap(tm.shared, sizeof(t_shared));
	return (0);
}
