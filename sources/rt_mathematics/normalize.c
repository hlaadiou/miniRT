/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:59:05 by azgaoua           #+#    #+#             */
/*   Updated: 2024/07/17 15:55:26 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_vector normal_at(t_object *sp, t_point pnt)
{
	t_tuple object_point;
	t_tuple object_normal;
	t_tuple world_normal;

	object_point = mtx_tuple_prod(sp->transform, pnt);
	object_normal = subtract_tuples(object_point, _point(0, 0, 0));
	world_normal = mtx_tuple_prod(mtx_transpose(sp->transform), object_normal);
	world_normal.w = 0;
	if (!world_normal.x && !world_normal.y && !world_normal.z)
		printf("world_normal~(normal_at) --- (%f, %f, %f, %f)\n", world_normal.x, world_normal.y, world_normal.z, world_normal.w);
	return (vec_normalize(world_normal));
}

