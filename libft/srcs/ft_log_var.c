/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_log_var.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/28 21:17:15 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2017/11/28 21:17:15 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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
