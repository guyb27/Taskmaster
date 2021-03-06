/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_log_params.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:06:15 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:06:15 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_get_log_params(int *argc, char *argv[])
{
	if (*argc > 1)
	{
		if (!ft_strcmp("--all", argv[*argc - 1]))
			g_log_lvl = 0;
		else if (!ft_strcmp("--debug", argv[*argc - 1]))
			g_log_lvl = 1;
		else if (!ft_strcmp("--error", argv[*argc - 1]))
			g_log_lvl = 2;
		else if (!ft_strcmp("--fatal", argv[*argc - 1]))
			g_log_lvl = 3;
		else if (!ft_strcmp("--info", argv[*argc - 1]))
			g_log_lvl = 4;
		else if (!ft_strcmp("--trace", argv[*argc - 1]))
			g_log_lvl = 6;
		else if (!ft_strcmp("--warn", argv[*argc - 1]))
			g_log_lvl = 7;
	}
	if (g_log_lvl == 5)
		return (0);
	else
	{
		*argc -= 1;
		return (1);
	}
}
