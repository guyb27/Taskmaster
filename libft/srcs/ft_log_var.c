/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:06:16 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:06:16 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	See ft_log.c for more details
*/

void		ft_log_var(int log_lvl, const char *func, char *message, void *var)
{
	char	*tmp;

	if (!g_log_lvl || log_lvl == g_log_lvl)
	{
		ft_log(log_lvl, func, "");
		tmp = NULL;
		if (ft_strstr_int(message, "%d"))
			tmp = ft_str_replace(message, "%d", ft_itoa((size_t)var));
		else if (ft_strstr_int(message, "%i"))
			tmp = ft_str_replace(message, "%i", ft_itoa((size_t)var));
		else if (ft_strstr_int(message, "%s"))
			tmp = ft_str_replace(message, "%s", (char *)var);
		else if (ft_strstr_int(message, "%c"))
			tmp = ft_str_replace(message, "%c", (char *)var);
		if (tmp)
		{
			ft_putstr(tmp);
			free(tmp);
		}
		else
			ft_putstr(message);
	}
}
