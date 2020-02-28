/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:02:33 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:02:33 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char		*ft_getenv(char *str, char **env)
{
	int		i;
	int		j;

	i = -1;
	if (env)
		while (env[++i])
		{
			j = 0;
			while (env[i][j] == str[j] && env[i][j] && str[j])
				j++;
			if (env[i][j] == '=' && j != 0 && !str[j])
				return (ft_strdup((env[i]) + (j + 1)));
		}
	return (NULL);
}
