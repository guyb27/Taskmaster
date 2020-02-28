/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 05:55:00 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 05:55:00 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "heart.h"

void		exit_shell(void)
{
	ft_strdel(&g_cl.cmd);
	ft_strdel(&g_cl.prompt);
	history_save((char ***)NULL, (char *)NULL, 2, (char *)NULL);
	get_next_line(-101, NULL);
}

int			read_server(int sock, char *buffer)
{
	int		n;

	ft_bzero(buffer, sizeof(buffer));
	if ((n = recv(sock, buffer, BUF_SIZE - 1, 0)) < 0)
	{
		ft_putstr("recv()\n");
		return (-1);
	}
	buffer[n] = '\0';
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
