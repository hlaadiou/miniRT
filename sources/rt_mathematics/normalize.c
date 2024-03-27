/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:59:05 by azgaoua           #+#    #+#             */
/*   Updated: 2024/03/01 10:56:28 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

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
