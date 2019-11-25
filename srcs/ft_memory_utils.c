/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_commands.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2060/00/00 18:14:45 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/24 03:11:54 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "taskmaster.h"

void			*ft_megamalloc(int size)
{
	void *var;

	var = mmap(NULL, size,
				PROT_READ | PROT_WRITE,
				MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	return (var);
}

void			ft_free_jobs(t_tm *tm)
{
	int			i;

	i = -1;
	printf("JOBS_COUNT: [%d]\n", tm->jobs_cnt);
	while (++i < tm->jobs_cnt)
		ft_tabdel(&tm->jobs[i].env);
	tm->jobs_cnt = 0;
}

int				ft_tabdel(char ***tab)
{
	int		i;

	i = -1;
	if (*tab)
	{
		while ((*tab)[++i])
			ft_strdel(&(*tab)[i]);
		free(*tab);
		*tab = NULL;
	}
	return (0);
}

char			**ft_tabdup(char **tab)
{
	int		i;
	char	**ret;

	i = -1;
	ret = NULL;
	if (!tab)
		return (NULL);
	if (!(ret = (char **)malloc(sizeof(char *) * (ft_tablen(tab) + 1))))
		return (NULL);
	while (tab[++i])
		ret[i] = ft_strdup(tab[i]);
	ret[i] = NULL;
	return (ret);
}
