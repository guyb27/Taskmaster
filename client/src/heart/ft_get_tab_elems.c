/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_get_tab_elems.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/16 05:05:35 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/16 09:22:13 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void			ft_get_tab_elems(char *str)
{
	char		**tablo;
	char		**tab_tmp;
	int i = 0;
	int j = 0;
	int k = 0;
	int			state;

	state = 0;
	tablo = ft_strsplit(str, '\n');
	while (j < 100)
	{
		ft_bzero(g_tab.cmd[j].cmd, sizeof(g_tab.cmd[j].cmd));
		ft_bzero(g_tab.process[j], sizeof(g_tab.process[j]));
		j++;
	}
	j = 0;
	ft_bzero(g_tab.cmd, sizeof(g_tab.cmd));
	ft_bzero(g_tab.process, sizeof(g_tab.process));
	while (tablo[i])
	{
		tab_tmp = ft_strsplit(tablo[i], ' ');
		if (tab_tmp && tab_tmp[0] && tab_tmp[0][0] == '\t')//CMD || PROCESS
		{
			if (state == 2)//COMMANDE
			{
				ft_strcpy(g_tab.cmd[j].cmd, tab_tmp[0] + 1);//COMMANDE
				if (tab_tmp[1])//PROCESS
				{
					g_tab.cmd[j].arg = 1;
					if (tab_tmp[2] && tab_tmp[3])//ALL
						g_tab.cmd[j].arg = 2;
				}
				j++;
			}
			else//PROCESS
				ft_strcpy(g_tab.process[k++], tab_tmp[0] + 1);
		}
		else//TITLE
			state++;
		ft_tabdel(&tab_tmp);
		i++;
	}
	ft_tabdel(&tablo);
}

int		ft_init_parse(int sock)
{
	int		i;
	char buffer[BUF_SIZE];
	int n;
	int j;
	int debut;

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
		{
			if (buffer[j] == '\0')
			{
				ft_putstr(buffer + debut);
				if (i == 1)
					ft_get_tab_elems(buffer + debut);
				else if (i == 2)
					g_cl.prompt = ft_strdup(buffer + debut);
				debut = j + 1;
				i++;
			}
			j++;
		}
	}
	return (0);
}
