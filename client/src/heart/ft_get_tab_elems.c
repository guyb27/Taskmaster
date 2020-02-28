/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_tab_elems.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 05:55:00 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 05:55:00 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "heart.h"

static void	ft_loop_get_tab_elems(char **tab_tmp, int *state, int *j, int *k)
{
	if (tab_tmp && tab_tmp[0] && tab_tmp[0][0] == '\t')
	{
		if (*state == 2)
		{
			ft_strcpy(g_cl.cmd_struct[*j].cmd, tab_tmp[0] + 1);
			if (tab_tmp[1])
			{
				g_cl.cmd_struct[*j].arg = 1;
				if (tab_tmp[2] && tab_tmp[3])
					g_cl.cmd_struct[*j].arg = 2;
			}
			*j = *j + 1;
		}
		else
		{
			ft_strcpy(g_cl.process[*k], tab_tmp[0] + 1);
			*k = *k + 1;
		}
	}
	else
		*state = *state + 1;
	ft_tabdel(&tab_tmp);
}

void		ft_get_tab_elems(char *str)
{
	char	**tablo;
	int		i;
	int		j;
	int		k;
	int		state;

	i = -1;
	j = -1;
	k = 0;
	state = 0;
	tablo = ft_strsplit(str, '\n');
	while (++j < 100)
	{
		ft_bzero(g_cl.cmd_struct[j].cmd, sizeof(g_cl.cmd_struct[j].cmd));
		ft_bzero(g_cl.process[j], sizeof(g_cl.process[j]));
	}
	j = 0;
	ft_bzero(g_cl.cmd_struct, sizeof(g_cl.cmd_struct));
	ft_bzero(g_cl.process, sizeof(g_cl.process));
	while (tablo[++i])
		ft_loop_get_tab_elems(ft_strsplit(tablo[i], ' '), &state, &j, &k);
	ft_tabdel(&tablo);
}

static void	ft_loop_init_parse(char buffer[], int *i, int *j, int *debut)
{
	if (buffer[*j] == '\0')
	{
		ft_putstr(buffer + *debut);
		if (*i == 1)
			ft_get_tab_elems(buffer + *debut);
		else if (*i == 2)
			g_cl.prompt = ft_strdup(buffer + *debut);
		*debut = *j + 1;
		*i = *i + 1;
	}
	*j = *j + 1;
}

int			ft_init_parse(int sock)
{
	int		i;
	char	buffer[BUF_SIZE];
	int		n;
	int		j;
	int		debut;

	i = 0;
	while (i < 3 && ft_memset(buffer, 0, sizeof(buffer)))
	{
		if (!(n = read_server(sock, buffer)) || n == -1)
		{
			ft_putstr(!n ? "Server disconnected !\n" : "");
			return (1);
		}
		j = 0;
		debut = 0;
		while (j < n)
			ft_loop_init_parse(buffer, &i, &j, &debut);
	}
	return (0);
}
