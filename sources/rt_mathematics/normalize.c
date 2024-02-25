/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:59:05 by azgaoua           #+#    #+#             */
/*   Updated: 2024/02/24 16:56:32 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_mathematics.h"
#include "../../includes/geometry.h"

t_vector normal_at(t_object *sp, t_point pnt)
{
	t_tuple object_point;
	t_tuple object_normal;
	t_tuple world_normal;

	object_point = mtx_tuple_prod(inverse(sp->transform), pnt);
	object_normal = subtract_tuples(object_point, _point(0, 0, 0));
	world_normal = mtx_tuple_prod(mtx_transpose(inverse(sp->transform)), object_normal);
	world_normal.w = 0;
	return (vec_normalize(world_normal));

}

// int main ()
// {
// 	t_object *s = _sphere(_point(0, 0, 0), 1);
// 	set_transform(&s, mtx_multiply(scaling_mtx(1, 0.5, 1) , rotation_z((3.14)/5)));
// 	t_vector n = normal_at(s, _point(0, sqrt(2) / 2, (-1) * (sqrt(2) / 2)));

// 	printf("n = (%.2f, %.2f, %.2f)", n.x, n.y, n.z);
// 	return (0);
// }