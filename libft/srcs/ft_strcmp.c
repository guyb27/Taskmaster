/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 06:06:18 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 06:06:18 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
		if (*s1++ != *s2++)
			return ((unsigned char)*(s1 - 1) - (unsigned char)*(s2 - 1));
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
