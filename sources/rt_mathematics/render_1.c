/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:11:06 by azgaoua           #+#    #+#             */
/*   Updated: 2024/07/28 12:48:22 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_ray	ray_for_pixel(t_camera_fn c, int px, int py)
{
	float		world_x;
	float		world_y;
	t_tuple		pixel;

	world_x = c.hwidth - (px + 0.5) * c.pixel_size;
	world_y = c.hheight - (py + 0.5) * c.pixel_size;
	pixel = mtx_tuple_prod(c.transform, _point(world_x, world_y, -1));
	return (_ray(mtx_tuple_prod(c.transform, _point(0, 0, 0)), \
			vec_normalize(subtract_tuples(pixel, \
				mtx_tuple_prod(c.transform, _point(0, 0, 0))))));
}

t_ray	ft_r1_and_caps(t_ray r, t_obj_lst *obj, t_inter ***xs, \
												t_lst_inter **lst)
{
	t_ray	r1;

	r1 = transform_ray(r, obj->obj->transform);
	(*xs) = intersect_caps(obj->obj, r1);
	if ((*xs))
		_intersections(lst, (*xs));
	return (r1);
}

t_lst_inter	*intersect_world(t_scene *w, t_ray r)
{
	t_lst_inter	*lst;
	t_inter		**xs;
	t_obj_lst	*obj;
	t_ray		r1;

	xs = NULL;
	lst = NULL;
	obj = w->lst;
	while (obj != NULL)
	{
		if (obj->obj->type == PLANE)
			xs = intersect_pl(r, obj->obj);
		else if (obj->obj->type == CYLINDER)
		{
			r1 = ft_r1_and_caps(r, obj, &xs, &lst);
			xs = local_intersect(obj->obj, r1);
		}
		else if (obj->obj->type == SPHERE)
			xs = intersect_sp(r, obj->obj);
		if (xs)
			_intersections(&lst, xs);
		obj = obj->next;
	}
	lst = lst_sort(lst);
	return (lst);
}

void	comps_init(t_comps **comps, t_inter *inter, t_ray ray)
{
	(*comps) = ft_malloc(sizeof(t_comps));
	(*comps)->inside = -1;
	(*comps)->t = inter->t;
	(*comps)->obj = inter->obj;
	(*comps)->point = _position(ray, (*comps)->t);
	(*comps)->eyev = multiply_tuple_scalar(-1, ray.dir);
	if ((*comps)->obj->type == SPHERE)
		(*comps)->normalv = normal_at((*comps)->obj, (*comps)->point);
	else if ((*comps)->obj->type == CYLINDER)
		(*comps)->normalv = local_normal_at((*comps)->obj, (*comps)->point);
	else if ((*comps)->obj->type == PLANE)
		(*comps)->normalv = (*comps)->obj->pl->vec;
}

t_comps	*prepare_computations(t_inter *inter, t_ray ray)
{
	t_comps	*comps;

	comps_init(&comps, inter, ray);
	if (dot_product(comps->normalv, comps->eyev) < 0 && \
			fabs(dot_product(comps->normalv, comps->eyev)) > 0.5f) /* critical part in the caps inside of a cylinder!! */
	{
		comps->inside = 1;
		comps->normalv = multiply_tuple_scalar(-1, comps->normalv);
	}
	else
		comps->inside = 0;
	if (((comps->obj->type == SPHERE && \
			(comps->obj->sp->radius * comps->t) >= 3.0f) || \
								(comps->obj->type == CYLINDER && \
			((comps->obj->cy->diameter / 2) * comps->t) >= 3.0f)) && \
														comps->inside == 0)
		comps->point = add_tuples(comps->point, \
						multiply_tuple_scalar(EPSILON, comps->normalv));
	else
		comps->point = add_tuples(comps->point, \
							multiply_tuple_scalar(0.00001f, comps->normalv));
	return (comps);
}
