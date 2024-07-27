/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:03:30 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/07/27 17:55:15 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

//5 params
// typedef struct s_cylinder
// {
// 	t_point		center;
// 	t_vector	axis;
// 	float		diameter;
// 	float		min;
// 	float		max;
// }	t_cylinder;

t_object	*_cylinder(t_point pt, t_vector axis, t_attributes attr, t_color c)
{
	t_cylinder	*cy;

	cy = (t_cylinder *)ft_malloc(sizeof(t_cylinder));
	if (!cy)
		return (NULL);
	*cy = (t_cylinder){pt, axis, attr.d, attr.min, attr.max};
	return (_obj(cy, c, CYLINDER));
}

t_inter	**intersect_pl(t_ray ray, t_object *plane)
{
	t_inter			**inter;
	t_roots			roots;
	t_vector		x;
	float			prod;

	inter = ft_malloc(sizeof(t_inter *) * 2);
	inter[0] = ft_malloc(sizeof(t_inter));
	inter[1] = ft_malloc(sizeof(t_inter));
	inter[0]->obj = NULL;
	inter[1]->obj = NULL;
	if (!dot_product(ray.dir, plane->pl->vec))
		return (NULL);
	x = subtract_tuples(ray.org, plane->pl->pt);
	prod = dot_product(ray.dir, plane->pl->vec) * \
						dot_product(x, plane->pl->vec);
	if (prod < EPSILON)
	{
		roots.counter = 1;
		roots.t1 = dot_product(multiply_tuple_scalar(-1.0, x), plane->pl->vec) \
		/ dot_product(ray.dir, plane->pl->vec);
		roots.t2 = roots.t1;
		inter = _intersection(roots, plane);
	}
	return (inter);
}

void	ft_inter_caps_init(t_inter ***inter)
{
	(*inter) = ft_malloc(sizeof(t_inter *) * 2);
	(*inter)[0] = ft_malloc(sizeof(t_inter));
	(*inter)[1] = ft_malloc(sizeof(t_inter));
	(*inter)[0]->obj = NULL;
	(*inter)[1]->obj = NULL;
}

t_inter	**intersect_caps(t_object *cy, t_ray r)
{
	t_inter	**inter;
	int		count;

	ft_inter_caps_init(&inter);
	count = 0;
	if (compare_f(r.dir.y, 0))
		return (NULL);
	if (check_cap(r, (cy->cy->min - r.org.y) / r.dir.y, cy))
	{
		inter[count]->t = (cy->cy->min - r.org.y) / r.dir.y;
		inter[count]->obj = cy;
		count++;
	}
	if (check_cap(r, (cy->cy->max - r.org.y) / r.dir.y, cy))
	{
		inter[count]->t = (cy->cy->max - r.org.y) / r.dir.y;
		inter[count]->obj = cy;
		count++;
	}
	if (count == 0)
		return (NULL);
	if (count == 1)
		inter[1] = NULL;
	return (inter);
}

int	check_cap(t_ray r, float t, t_object *cy)
{
	float	x;
	float	z;

	x = r.org.x + (t * r.dir.x);
	z = r.org.z + (t * r.dir.z);
	if (((x * x) + (z * z)) <= (powf(cy->cy->diameter, 2) / 4.0f))
		return (1);
	return (0);
}
