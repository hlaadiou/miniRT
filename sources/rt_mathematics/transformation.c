/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:11:31 by azgaoua           #+#    #+#             */
/*   Updated: 2024/07/20 17:25:26 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	set_transform(t_object **obj, t_matrix *mtx)
{
	if (!(*obj)->transform || !mtx)
		put_error("invalid transformation matrix\n");
	(*obj)->transform = mtx_multiply(mtx, (*obj)->transform);
}

t_ray	transform(t_ray ray, t_matrix *a)
{
	t_ray	b;

	b = _ray(ray.org, ray.dir);
	b.org = mtx_tuple_prod(a, ray.org);
	b.dir = mtx_tuple_prod(a, ray.dir);
	return (b);
}
