/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 11:26:14 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/02/18 15:39:29 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/geometry.h"

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

t_quadratic	discriminant(t_ray ray, t_sphere sp)
{
	t_vector	sp_to_ray;
	t_quadratic	quad;

	sp_to_ray = substract_tuples(ray.org, sp.org);
	quad.a = dot_product(ray.dir, ray.dir);
	quad.b = 2 * dot_product(ray.dir, sp_to_ray);
	quad.c = dot_product(sp_to_ray, sp_to_ray) - 1;
	quad.delta = pow(quad.b, 2) - (4 * quad.a * quad.c);
	return (quad);
}

t_intersection	intersect(t_ray ray, t_sphere sp)
{
	t_quadratic		quad;
	t_intersection	i;

	quad = discriminant(ray, sp);
	if (quad.delta < 0)
		i = (t_intersection){0.0, 0.0, 0};
	else
	{
		i.t1 = ((-1 * quad.b) - sqrt(quad.delta)) / (2 * quad.a);
		i.t2 = ((-1 * quad.b) + sqrt(quad.delta)) / (2 * quad.a);
		i.counter = 2;
	}
	return (i);
}


int	main(void)
{
	t_ray ray = _ray(_point(0, 0, 5), _vector(0, 0, 1));
	t_sphere sp = _sphere(_point(0, 0, 0), 1.0);
	t_intersection inter = intersect(ray, sp);

	printf("%.2f, %.2f, %d\n", inter.t1, inter.t2, inter.counter);
}

