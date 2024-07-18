/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:46:44 by hlaadiou          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/07/16 10:42:58 by hlaadiou         ###   ########.fr       */
=======
/*   Updated: 2024/07/17 00:16:24 by azgaoua          ###   ########.fr       */
>>>>>>> J-9
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/* generates an object type from sphere/cylinder/plan */
t_object	*_obj(void *obj, t_color c, t_types type)
{
	t_object	*o;

	if (!obj)
		return (NULL);
	o = (t_object*)ft_malloc(sizeof(t_object));
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

t_ray transform_ray(t_ray ray, t_matrix *a)
{
    t_ray b;

    b = _ray(ray.org, ray.dir);
    b.org =  mtx_tuple_prod(a, ray.org);
    b.dir =  mtx_tuple_prod(a, ray.dir);
    return (b);
}
