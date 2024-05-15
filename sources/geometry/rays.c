/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 11:26:14 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/05/15 16:37:40 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/* CREATES AN ARRAY OF TWO INTERSECTIONS OR RETURNS NULL IF NONE ARE FOUND */
/* PROBABLY USELESS | NEEDS PEER REVIEW | */
t_inter	**_intersection(t_roots roots, t_object *obj)
{
	t_inter	**inter;

	if (!roots.counter)
		return (NULL);
	inter = (t_inter **)malloc(sizeof(t_inter *) * 2);
	if (!inter)
		return (NULL);
	inter[0] = (t_inter *)malloc(sizeof(t_inter));
	if (!inter[0])
		return (free(inter), NULL);
	inter[1] = (t_inter *)malloc(sizeof(t_inter));
	if (!inter[1])
		return (free(inter[0]), free(inter), NULL);
	*inter[0] = (t_inter){roots.t1, obj};
	*inter[1] = (t_inter){roots.t2, obj};
	return (inter);
}

t_ray	*_ray(t_point org, t_vector vec)
{
	t_ray	*ray;

	ray = (t_ray *)malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	*ray = (t_ray){org, vec};
	return (ray);
}

t_point	_position(t_ray *ray, float t)
{
	return (add_tuples(ray->org, multiply_tuple_scalar(t, ray->dir)));
}

/* We assume that the obj is a SPHERE */
t_quadratic	discriminant_sp(t_ray *ray, t_object *sp)
{
	t_vector	sp_to_ray;
	t_quadratic	quad;

	sp_to_ray = subtract_tuples(ray->org, sp->sp->org);
	quad.a = dot_product(ray->dir, ray->dir);
	quad.b = 2 * dot_product(ray->dir, sp_to_ray);
	quad.c = dot_product(sp_to_ray, sp_to_ray) - sp->sp->radius;
	quad.delta = pow(quad.b, 2) - (4 * quad.a * quad.c);
	return (quad);
}

/* We assume that the obj is a SPHERE */
t_inter	**intersect_sp(t_ray *ray, t_object *sp)
{
	t_inter			**inter;
	t_quadratic		quad;
	t_roots			r;
	
	quad = discriminant_sp(transform(ray, sp->transform), sp); /* change the  discriminant_sp(^ray, sp) by discriminant_sp(^ray2, sp) */
	if (quad.delta < 0)
		r = (t_roots){0.0, 0.0, 0};
	else
	{
		r.t1 = ((-1 * quad.b) - sqrt(quad.delta)) / (2 * quad.a);
		r.t2 = ((-1 * quad.b) + sqrt(quad.delta)) / (2 * quad.a);
		r.counter = 2;
	}
	inter = _intersection(r, sp); /* returns an array of two inters, or NULL */
	return (inter);
}
