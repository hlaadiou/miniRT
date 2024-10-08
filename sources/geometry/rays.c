/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 11:26:14 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/07/29 14:27:44 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/* CREATES AN ARRAY OF TWO INTERSECTIONS OR RETURNS NULL IF NONE ARE FOUND */
t_inter	**_intersection(t_roots roots, t_object *obj)
{
	t_inter	**inter;

	if (!roots.counter)
		return (NULL);
	inter = (t_inter **)ft_malloc(sizeof(t_inter *) * 2);
	if (!inter)
		return (NULL);
	inter[0] = (t_inter *)ft_malloc(sizeof(t_inter));
	if (!inter[0])
		return (NULL);
	inter[1] = (t_inter *)ft_malloc(sizeof(t_inter));
	if (!inter[1])
		return (NULL);
	*inter[0] = (t_inter){roots.t1, obj};
	*inter[1] = (t_inter){roots.t2, obj};
	return (inter);
}

t_ray	_ray(t_point org, t_vector vec)
{
	t_ray	ray;

	ray = (t_ray){org, vec};
	return (ray);
}

t_point	_position(t_ray ray, float t)
{
	return (add_tuples(ray.org, multiply_tuple_scalar(t, ray.dir)));
}

t_quadratic	discriminant_sp(t_ray ray, t_object *sp)
{
	t_vector	sp_to_ray;
	t_quadratic	quad;

	sp_to_ray = subtract_tuples(ray.org, sp->sp->org);
	quad.a = dot_product(ray.dir, ray.dir);
	quad.b = 2 * dot_product(ray.dir, sp_to_ray);
	quad.c = dot_product(sp_to_ray, sp_to_ray) - sp->sp->radius;
	quad.delta = powf(quad.b, 2) - (4 * quad.a * quad.c);
	return (quad);
}

t_inter	**intersect_sp(t_ray ray, t_object *sp)
{
	t_inter			**inter;
	t_quadratic		quad;
	t_roots			r;

	quad = discriminant_sp(transform(ray, sp->transform), sp);
	if (quad.delta < 0)
		r = (t_roots){0.0, 0.0, 0};
	else
	{
		r.t1 = ((-1 * quad.b) - sqrt(quad.delta)) / (2 * quad.a);
		r.t2 = ((-1 * quad.b) + sqrt(quad.delta)) / (2 * quad.a);
		r.counter = 2;
	}
	inter = _intersection(r, sp);
	return (inter);
}
