/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_getters_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:03:30 by azgaoua           #+#    #+#             */
/*   Updated: 2024/07/20 17:04:01 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pars.h"
#include "../../includes/lighting.h" 

void	free_object(t_object *obj)
{
	if (obj->type == SPHERE)
		free(obj->sp);
	else if (obj->type == PLANE)
		free(obj->pl);
	else if (obj->type == CYLINDER)
		free(obj->cy);
	free_f_mtx(obj->transform->mtx, obj->transform->size);
	free(obj->transform);
	free(obj);
}

void	object_fatal(t_obj_lst *lst)
{
	t_obj_lst	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free_object(tmp->obj);
		free(tmp);
	}
	put_error("Fatal, Memory error: unable to create node\n");
}

t_obj_lst	*get_objs_data(t_pars *conf)
{
	t_obj_lst	*lst;
	t_object	*obj;

	lst = NULL;
	obj = NULL;
	while (conf)
	{
		if (conf->flag == SP || conf->flag == PL || conf->flag == CY)
		{
			obj = check_objs_data(conf);
			if (obj)
				obj_list_add(&lst, obj);
		}
		conf = conf->next;
	}
	return (lst);
}
