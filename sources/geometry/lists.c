/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:55:46 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/04/03 06:49:51 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_lst_inter	*new_intersection(t_inter *inter)
{
	t_lst_inter	*node;

	node = (t_lst_inter *)malloc(sizeof(t_lst_inter));
	if (!node)
		return (NULL);
	node->inter = inter;
	node->next = NULL;
	return (node);
}

int	inter_list_add(t_lst_inter **list, t_inter *inter)
{
	t_lst_inter	*tmp;

	tmp = *list;
	if (!tmp)
	{
		*list = new_intersection(inter);
		tmp = *list;
		if (tmp)
			tmp->prev = NULL;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_intersection(inter);
		tmp->next->prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return (1);
	return (0);
}

int	_intersections(t_lst_inter **lst, t_inter **i)
{
	if (!i)
		return (-1);
	if (inter_list_add(lst, i[0]))
		return (free(i[0]), free(i[1]), free(i), 1);
	if (inter_list_add(lst, i[1]))
		return (free(i[1]), free(i), 1);
	return (0);
}

t_lst_inter	*lst_last(t_lst_inter *inters)
{
	if (!inters)
		return (NULL);
	while (inters->next)
		inters = inters->next;
	return (inters);
}
