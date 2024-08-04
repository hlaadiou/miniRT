/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:14:31 by azgaoua           #+#    #+#             */
/*   Updated: 2024/07/28 18:45:56 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_matrix	*axis_cylinder(t_vector orie)
{
	t_vector	up;
	t_vector	forw;
	t_vector	right;

	if (orie.x == 0 && orie.z == 0)
	{
		if (orie.y >= 0)
		{
			up = _vector(0, 1, 0);
			right = _vector(1, 0, 0);
		}
		else
		{
			up = _vector(0, -1, 0);
			right = _vector(-1, 0, 0);
		}
		forw = _vector(0, 0, 1);
	}
	else
	{
		up = vec_normalize(orie);
		forw = vec_normalize(cross_product(_vector(0, 1, 0), up));
		right = cross_product(up, forw);
	}
	return (axis_to_matrix(right, up, forw));
}

void	set_transformations(t_obj_lst *lst)
{
	t_point		p;
	float		scale;

	while (lst)
	{
		p = get_obj_point(lst->obj);
		scale = get_diameter(lst->obj);
		scale = scale / 2.0f;
		if (lst->obj->type == SPHERE)
		{
			lst->obj->sp->org = _point(0, 0, 0);
			lst->obj->sp->radius = 1;
			lst->obj->transform = inverse(translation(p.x, p.y, p.z));
			set_transform(&lst->obj, inverse(scaling_mtx(scale, scale, scale)));
		}
		else if (lst->obj->type == CYLINDER)
		{
			lst->obj->cy->center = _point(0, 0, 0);
			lst->obj->transform = _identity(4);
			set_transform(&lst->obj, inverse(translation(p.x, p.y, p.z)));
			set_transform(&lst->obj, \
							inverse(axis_cylinder(lst->obj->cy->axis)));
		}
		lst = lst->next;
	}
}

t_color	color_at(t_scene *w, t_ray r)
{
	t_lst_inter	*lst;
	t_inter		*h;
	t_comps		*comps;
	t_color		color;

	lst = intersect_world(w, r);
	h = hit(lst);
	if (h == NULL || (h->obj && compare_f(h->t, 0.0f)) || h->obj == NULL)
		return (_color(0, 0, 0));
	comps = prepare_computations(h, r);
	color = shade_hit(w, comps);
	return (color);
}

t_color	shade_hit(t_scene *world, t_comps *copms)
{
	int	shadowed;

	shadowed = is_shadowed(world, copms->point);
	return (illuminate(copms, world, shadowed));
}

t_matrix	*axis_to_matrix(t_vector up, t_vector forw, t_vector right)
{
	t_matrix	*res;

	res = _identity(4);
	res->mtx[0][0] = up.x;
	res->mtx[1][0] = up.y;
	res->mtx[2][0] = up.z;
	res->mtx[0][1] = forw.x;
	res->mtx[1][1] = forw.y;
	res->mtx[2][1] = forw.z;
	res->mtx[0][2] = right.x;
	res->mtx[1][2] = right.y;
	res->mtx[2][2] = right.z;
	return (res);
}
