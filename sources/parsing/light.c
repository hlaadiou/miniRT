/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:20:07 by azgaoua           #+#    #+#             */
/*   Updated: 2024/07/17 00:17:29 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pars.h"

t_pars	*ft_lstnew(char *content, char **elms, int flag)
{
	t_pars	*new;

	new = (t_pars *)ft_malloc(sizeof(t_pars));
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
	char	**tab;

	tab = str_split(line, " \t\r\f\n\v");
	if (ft_tab_size(tab) != 4)
	{
		ft_putstr_fd("Error\nwrong number of specific informations\n", 2);
		exit(1);
	}
	ft_lstadd_back(pars, ft_lstnew(tab[0], tab, 3));
}
