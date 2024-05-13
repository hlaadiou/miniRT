/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:46:44 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/05/09 17:16:59 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/* generates an object type from sphere/cylinder/plan */
t_object	*_obj(void *obj, t_color c, t_types type)
{
	t_object	*o;

	if (!obj)
		return (NULL);
	o = (t_object*)malloc(sizeof(t_object));
	if (!o)
		return (NULL);
	if (type == SPHERE)
	{
		*o = (t_object){SPHERE, (t_sphere*)obj, NULL, NULL, _identity(4), \
		_specs(0.1, 0.9, 0.9, 200.0), c};
	}
	else if (type == CYLINDER)
	{	
		*o = (t_object){CYLINDER, NULL, (t_cylinder*)obj, NULL, _identity(4), \
		_specs(0.1, 0.9, 0.9, 200.0), c};
	}
	else if (type == PLANE)
	{
		*o = (t_object){PLANE, NULL, NULL, (t_plane*)obj, _identity(4), \
		_specs(0.1, 0.9, 0.9, 200.0), c};
	}
	return (o);
}

t_ray *transform_ray(t_ray *ray, t_matrix *a)
{
    t_ray *b;

    b = _ray(ray->org, ray->dir);
    b->org =  mtx_tuple_prod(a, ray->org);
    b->dir =  mtx_tuple_prod(a, ray->dir);
    return (b);
}
