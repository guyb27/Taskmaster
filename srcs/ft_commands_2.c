/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 05:53:34 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 05:53:34 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster.h"

static void	ft_free_jobs(t_tm *tm)
{
	int			i;
	t_status	*status;
	t_status	*tmp;

	i = -1;
	while (++i < tm->jobs_cnt)
	{
		ft_tabdel(&tm->jobs[i].env);
		status = tm->shared->status[i].next;
		while (status)
		{
			tmp = status->next;
			munmap(status, sizeof(status));
			status = tmp;
		}
	}
	tm->jobs_cnt = 0;
}

void		ft_quit(t_tm *tm)
{
	int			i;

	ft_printf("Quitting taskmaster\n");
	ft_free_jobs(tm);
	munmap(tm->shared, sizeof(t_shared));
	ft_strdel(&tm->ret);
	i = 0;
	while (i < tm->server.clients_cnt)
		close(tm->server.clients[i++]);
	close(tm->server.sock);
	close(tm->server.csock);
	exit(0);
}

void		ft_reload(t_tm *tm)
{
	ft_cmd_stop(tm, "all");
	ft_free_jobs(tm);
	ft_parse_config(tm);
	ft_autostart_jobs(tm);
	ft_strdel(&tm->ret);
	tm->ret = ft_cmd_help(tm);
	ft_printf("Config file reloaded\n");
}

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
	ft_sprintf(&ret, "%s\texit\n", ret);
	ft_sprintf(&ret, "%sprocess list:\n", ret);
	while (i < tm->jobs_cnt)
		ft_sprintf(&ret, "%s\t%s\n", ret, tm->jobs[i++].name);
	return (ret);
}
