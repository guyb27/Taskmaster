/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_search_tab.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 10:56:07 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/26 10:37:08 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int		search_bin_tab(t_shell **ed)
{
	if (!(*ed)->t.word || 0 == ft_strncmp((*ed)->t.word, "status", ft_strlen((*ed)->t.word)))
		ft_malloc_cmd(&(*ed)->t.elem, "status");
	if (!(*ed)->t.word || 0 == ft_strncmp((*ed)->t.word, "start", ft_strlen((*ed)->t.word)))
		ft_malloc_cmd(&(*ed)->t.elem, "start");
	if (!(*ed)->t.word || 0 == ft_strncmp((*ed)->t.word, "restart", ft_strlen((*ed)->t.word)))
		ft_malloc_cmd(&(*ed)->t.elem, "restart");
	if (!(*ed)->t.word || 0 == ft_strncmp((*ed)->t.word, "pause", ft_strlen((*ed)->t.word)))
		ft_malloc_cmd(&(*ed)->t.elem, "pause");
	if (!(*ed)->t.word || 0 == ft_strncmp((*ed)->t.word, "stop", ft_strlen((*ed)->t.word)))
		ft_malloc_cmd(&(*ed)->t.elem, "stop");
	if (!(*ed)->t.word || 0 == ft_strncmp((*ed)->t.word, "reload", ft_strlen((*ed)->t.word)))
		ft_malloc_cmd(&(*ed)->t.elem, "reload");
	if (!(*ed)->t.word || 0 == ft_strncmp((*ed)->t.word, "help", ft_strlen((*ed)->t.word)))
		ft_malloc_cmd(&(*ed)->t.elem, "help");
	return (0);
}

int		search_in_rep_tab(t_shell **ed)
{
	if (!(*ed)->t.word || 0 == ft_strncmp((*ed)->t.word, "Bonjour", ft_strlen((*ed)->t.word)))
		ft_malloc_cmd(&(*ed)->t.elem, "Bonjour");
	if (!(*ed)->t.word || 0 == ft_strncmp((*ed)->t.word, "Bonjour les amis", ft_strlen((*ed)->t.word)))
		ft_malloc_cmd(&(*ed)->t.elem, "Bonjour les amis");
	if (!(*ed)->t.word || 0 == ft_strncmp((*ed)->t.word, "Au revoir", ft_strlen((*ed)->t.word)))
		ft_malloc_cmd(&(*ed)->t.elem, "Au revoir");
	return (0);
}

char	**search_var_tab(char *word)
{
	char	**ret;


	ret = NULL;
	ft_malloc_cmd(&ret, "HELLO WORLD");
	ft_malloc_cmd(&ret, "HELLO");
	return (ret);
}
