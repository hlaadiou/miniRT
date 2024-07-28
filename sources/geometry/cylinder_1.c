/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:15:26 by azgaoua           #+#    #+#             */
/*   Updated: 2024/07/28 16:45:00 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_vector	local_normal_at(t_object *cy, t_point world_point)
{
	t_point			object_point;
	t_vector		normal;
	float			dist;

	object_point = mtx_tuple_prod(cy->transform, world_point);
	dist = powf(object_point.x, 2) + powf(object_point.z, 2);
	if (dist < powf(cy->cy->diameter / 2.0f, 2.0f) && \
				object_point.y >= cy->cy->max - EPSILON)
	{
		normal = (t_vector){0, 1, 0, 1};
		normal = mtx_tuple_prod(mtx_transpose(cy->transform), normal);
	}
	else if (dist < powf(cy->cy->diameter / 2.0f, 2.0f) && \
				object_point.y <= cy->cy->min + EPSILON)
	{
		normal = (t_vector){0, -1, 0, 1};
		normal = mtx_tuple_prod(mtx_transpose(cy->transform), normal);
	}
	else
	{
		normal = (t_vector){object_point.x, 0, object_point.z, 1};
		normal = mtx_tuple_prod(mtx_transpose(cy->transform), normal);
	}
	return (normal);
}
