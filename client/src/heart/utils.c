/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sh42_exit.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 16:21:36 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/16 06:08:12 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void		exit_shell(void)
{
	ft_strdel(&g_cmd);
	history_save((char ***)NULL, (char *)NULL, 2, (char *)NULL);
	get_next_line(-101, NULL);
}

int			read_server(int sock, char *buffer)
{
	int		n;

	if ((n = recv(sock, buffer, BUF_SIZE - 1, 0)) < 0)
	{
		ft_putstr("recv()\n");
		return (-1);
	}
	buffer[n] = 0;
	return (n);
}

int			write_server(int sock, const char *buffer)
{
	if (send(sock, buffer, strlen(buffer), 0) < 0)
	{
		ft_putstr("send()\n");
		return (-1);
	}
	return (0);
}
