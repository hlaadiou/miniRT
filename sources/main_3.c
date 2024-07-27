/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:13:30 by azgaoua           #+#    #+#             */
/*   Updated: 2024/07/27 19:02:19 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	compare_ff(float a, float b)
{
	if (fabs(a - b) < 0.000001f)
		return (1);
	else
		return (0);
}

int	is_shadowed(t_scene *w, t_point p)
{
	t_vector		v;
	float			distance;
	t_ray			r;
	t_inter			*h;
	t_lst_inter		*lst;

	v = subtract_tuples(w->light.position, p);
	distance = vec_magnitude(v);
	r = _ray(p, vec_normalize(v));
	lst = intersect_world(w, r);
	h = hit(lst);
	if (h != NULL && (compare_ff(fabs(h->t - distance), 0)))
		return (1);
	if (h != NULL && (h->t < distance))
		return (1);
	return (0);
}

t_camera_fn	set_camera(t_camera cam)
{
	t_camera_fn	c;

	c = camera(WIDTH, HEIGHT, cam.fov * (M_PI / 180));
	c.transform = inverse(view_transform(cam.view_point, \
					add_tuples(cam.view_point, cam.orientation), \
					_point(0, 1, 0)));
	return (c);
}

t_point	get_obj_point(t_object *obj)
{
	if (obj->type == SPHERE)
		return (obj->sp->org);
	else if (obj->type == CYLINDER)
		return (obj->cy->center);
	else if (obj->type == PLANE)
		return (obj->pl->pt);
	return ((t_point){0});
}

float	get_diameter(t_object *obj)
{
	if (obj->type == SPHERE)
		return (obj->sp->radius);
	else if (obj->type == CYLINDER)
		return (obj->cy->diameter);
	return (1.0);
}
