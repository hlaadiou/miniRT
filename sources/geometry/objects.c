/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:46:44 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/02/20 18:00:17 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/geometry.h"

/* generates an object type from sphere/cylinder/plan */
t_object	*_obj(void *obj, t_types type)
{
	t_object	*o;

	if (!obj)
		return (NULL);
	o = (t_object*)malloc(sizeof(t_object));
	if (!o)
		return (NULL);
	if (type == SPHERE)
		*o = (t_object){SPHERE, (t_sphere*)obj, NULL, NULL};
	else if (type == CYLINDER)
		*o = (t_object){CYLINDER, NULL, (t_cylinder*)obj, NULL};
	else if (type == PLANE)
		*o = (t_object){PLANE, NULL, NULL, (t_plane*)obj};
	return (o);
}

void	set_obj(t_object *obj, t_inter *inter)
{
	if (!obj || !inter)
		return ;
	if (obj->type == SPHERE)
	{
		inter->obj->type = SPHERE;
		inter->obj->sp = obj->sp;
	}
	else if (obj->type == CYLINDER)
	{
		inter->obj->type = CYLINDER;
		inter->obj->cy = obj->cy;
	}
	else if (obj->type == PLANE)
	{
		inter->obj->type = PLANE;
		inter->obj->pl = obj->pl;
	}
}
