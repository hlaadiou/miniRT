/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 21:00:06 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/07/16 01:14:45 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pars.h"

t_obj_lst	*new_obj_node(t_object *obj)
{
	t_obj_lst	*node;

	node = (t_obj_lst *)malloc(sizeof(t_obj_lst));
	if (!node)
		return (NULL);
	node->obj = obj;
	node->next = NULL;
	return (node);
}

int	obj_list_add(t_obj_lst **list, t_object *obj)
{
	t_obj_lst	*tmp;

	tmp = *list;
	if (!tmp)
	{
		*list = new_obj_node(obj);
		tmp = *list;
		if (tmp)
			tmp->prev = NULL;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_obj_node(obj);
		tmp->next->prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return (1);
	return (0);
}

t_obj_lst	*obj_lst_last(t_obj_lst *objs)
{
	if (!objs)
		return (NULL);
	while (objs->next)
		objs = objs->next;
	return (objs);
}
