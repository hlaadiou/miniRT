/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hits.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:53:04 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/07/25 11:12:23 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/* RETURNS THE LOWEST NONNEGATIVE INTERSECTION
** !! WARNING !! WE ASSUME THAT THE HIT WILL BE 'IF ANY' IN THE BEGINNING 
** 		OF THE LIST
** THIS COULD NOT BE THE CASE! */
t_inter	*hit(t_lst_inter *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (lst->inter && lst->inter->t >= EPSILON)
			return (lst->inter);
		lst = lst->next;
	}
	return (NULL);
}

/*
** b ==> 2 * ((r.dir.x * r.org.x) + (r.dir.z * r.org.z))
** c = (r.org.x * r.org.x) + (r.org.z * r.org.z) - (powf(cy->cy->diameter, 2) / 4.0f)
** a = (r.dir.x * r.dir.x) + (r.dir.z * r.dir.z)
*/

t_inter	**ft_local_intersect_2(float a, t_object *cy, float c, t_ray r)
{
	float		sqrt_discriminant;
	float		t1;
	float		t2;
	t_inter		**inter;

	sqrt_discriminant = sqrt(2 * ((r.dir.x * r.org.x) + \
							(r.dir.z * r.org.z)) * 2 * ((r.dir.x * r.org.x) + \
							(r.dir.z * r.org.z)) - (4 * a * c));
	t1 = (-2 * ((r.dir.x * r.org.x) + (r.dir.z * r.org.z)) - \
							sqrt_discriminant) / (2 * a);
	t2 = (-2 * ((r.dir.x * r.org.x) + (r.dir.z * r.org.z)) + \
							sqrt_discriminant) / (2 * a);
	inter = ft_malloc(sizeof(t_inter *) * 2);
	if (t1 < 0 && t2 < 0)
		return (NULL);
	inter[0] = ft_malloc(sizeof(t_inter));
	inter[1] = ft_malloc(sizeof(t_inter));
	if (t1 > t2)
	{
		sqrt_discriminant = t1;
		t1 = t2;
		t2 = sqrt_discriminant;
	}
	sqrt_discriminant = r.org.y + (t1 * r.dir.y);
	if (cy->cy->min < sqrt_discriminant && sqrt_discriminant < cy->cy->max)
	{
		inter[0]->t = t1;
		inter[0]->obj = cy;
	}
	sqrt_discriminant = r.org.y + (t2 * r.dir.y);
	if (cy->cy->min < sqrt_discriminant && sqrt_discriminant < cy->cy->max)
	{
		inter[1]->t = t2;
		inter[1]->obj = cy;
	}
	return (inter);
}

t_inter	**local_intersect(t_object *cy, t_ray r)
{
	float	a;
	float	b;
	float	c;
	float	discriminant;

	a = (r.dir.x * r.dir.x) + (r.dir.z * r.dir.z);
	if (fabs(a) < 0 || fabs(r.dir.y) < 0)
		return (NULL);
	b = 2 * ((r.dir.x * r.org.x) + (r.dir.z * r.org.z));
	c = (r.org.x * r.org.x) + (r.org.z * r.org.z) - (powf(cy->cy->diameter, \
																2) / 4.0f);
	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (NULL);
	return (ft_local_intersect_2(a, cy, c, r));
}
