/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:20:07 by azgaoua           #+#    #+#             */
/*   Updated: 2024/03/13 12:10:47 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pars.h"

t_pars	*ft_lstnew(char *content, char **elms, int flag)
{
	t_pars	*new;

	new = malloc(sizeof(t_pars));
	if (!new)
		return (0);
	new -> identifier = content;
	new -> elements = elms;
	new -> flag = flag;
	new -> next = NULL;
	return (new);
}

void	ft_lstadd_back(t_pars **lst, t_pars *new)
{
	t_pars	*last;

	if (!lst)
		return ;
	last = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		while (last -> next != NULL)
			last = last -> next;
		last -> next = new;
	}
}

void	ft_light(char *line, t_pars **pars)
{
		t_pars	*new;
	char	**tab;

	tab = str_split(line, " \t\r\f\n\v");
	if (ft_tab_size(tab) != 4)
		exit(0);
	new = ft_lstnew(tab[0], tab, 3);
	ft_lstadd_back(pars, new);
	// free_tab(tab);
}
