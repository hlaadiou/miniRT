/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:11:31 by azgaoua           #+#    #+#             */
/*   Updated: 2024/02/21 21:14:44 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/geometry.h"

void	set_transform(t_object **obj, t_matrix *mtx)
{
	(*obj)->transform = mtx_multiply((*obj)->transform, mtx);
}

t_ray	*transform(t_ray *ray, t_matrix *a)
{
	t_ray *b;

	b = _ray(ray->org, ray->dir);
	b->org =  mtx_tuple_prod(a, ray->org);
	b->dir =  mtx_tuple_prod(a, ray->dir);
	return (b);
}

// int main()
// {
// 	// t_ray		*r = _ray(_point(1, 2, 3), _vector(0, 1, 0));
// 	// t_matrix	*m = scaling_mtx(2, 3, 4);
// 	// t_ray		*r2 = transform(r, m);

// 	// printf("r2.origin : (%.2f , %.2f, %.2f)\n", r2->org.x, r2->org.y, r2->org.z);
// 	// printf("r2.direction : (%.2f , %.2f, %.2f)\n", r2->dir.x, r2->dir.y, r2->dir.z);
// 	t_ray *r = _ray(_point(0, 0, -5), _vector(0, 0, 1));
// 	t_object *s = _sphere(_point(0.0, 0.0, 0.0), 1);
// 	set_transform(&s, scaling_mtx(2, 2, 2));
// 	t_inter **xs =  intersect_sp(r, s);
// 	if (xs)
// 	{
// 		printf("xs.count = 2\n");
// 		printf("xs[0]->t = %.2f\n", xs[0]->t);
// 		printf("xs[1]->t = %.2f\n", xs[1]->t);
// 	}
// 	else
// 		printf("xs.count = 0\n");

	
// }