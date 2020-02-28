/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 05:53:34 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/28 05:53:34 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "taskmaster.h"

void	ft_append_int_val(int list[], int val)
{
	int	i;

	i = 0;
	while (list[i] > -42)
		i++;
	list[i] = val;
}

void	ft_append_env(t_job *job, char *key, char *value)
{
	char *entry;

	entry = NULL;
	ft_sprintf(&entry, "%s=%s", key, value);
	if (job->env)
	{
		job->env = realloc(job->env, (ft_tablen(job->env) + 2) * sizeof(char*));
		job->env[ft_tablen(job->env) + 1] = NULL;
	}
	else
	{
		job->env = ft_memalloc(2 * sizeof(char*));
	}
	(job->env)[ft_tablen(job->env)] = strdup(entry);
	free(entry);
}
