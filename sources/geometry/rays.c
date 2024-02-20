/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 11:26:14 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/02/20 18:46:40 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/geometry.h"

t_inter	**_intersection(t_roots roots, void *obj)
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
	quad.c = dot_product(sp_to_ray, sp_to_ray) - 1;
	quad.delta = pow(quad.b, 2) - (4 * quad.a * quad.c);
	return (quad);
}

/* We assume that the obj is a SPHERE */
t_inter	**intersect_sp(t_ray *ray, t_object *sp)
{
	t_inter			**inter;
	t_quadratic		quad;
	t_roots			i;

	quad = discriminant_sp(ray, sp);
	if (quad.delta < 0)
		i = (t_roots){0.0, 0.0, 0};
	else
	{
		i.t1 = ((-1 * quad.b) - sqrt(quad.delta)) / (2 * quad.a);
		i.t2 = ((-1 * quad.b) + sqrt(quad.delta)) / (2 * quad.a);
		i.counter = 2;
	}
	inter = _intersection(i, sp); // returns an array of two inters, or NULL
	return (inter);
}

// int	main(void)
// {
// 	t_ray *ray = _ray(_point(0, 0, 0), _vector(0, 0, 1));
// 	t_object *sp = _sphere(_point(0, 0, 0), 1.0);
// 	t_lst_inter *inter = NULL;

// 	_intersections(&inter, intersect_sp(ray, sp));
// 	while (inter)
// 	{
// 		printf("%.2f  || %.2f\n", inter->inter->t, inter->inter->obj->sp->radius);
// 		inter = inter->next;
// 	}
// 	return (0);
// }