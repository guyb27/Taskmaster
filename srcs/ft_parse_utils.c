/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parse_utils.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2060/00/00 18:14:45 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2066/01/02 18:14:46 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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
