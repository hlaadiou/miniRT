/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:19:01 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/07/16 11:40:35 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/*
 *------ PHONG COMPONENT ------*
	* a : ambient component
	* d : diffuse component
	* s : specular component
	* ph : phong coefficient (shininess)
*/

t_phong	_phong(t_object *obj, t_point px, t_light light, t_point cam)
{
	t_phong	phong;

	phong.px_color = schur_product(obj->color, light.color);
	phong.ambient = multiply_color_scalar(obj->specs.ambient, phong.px_color);
	phong.diffuse = _color(0, 0, 0);
	phong.specular = _color(0, 0, 0);
	if (obj->type == SPHERE)
		phong.n = normal_at(obj, px);
	else if (obj->type == CYLINDER)
	{
		phong.n = local_normal_at(obj, px);
	}
	else if (obj->type == PLANE)
		phong.n = vec_normalize(obj->pl->vec);
	phong.l = vec_normalize(subtract_tuples(light.position, px));
	phong.r = reflect(multiply_tuple_scalar(-1, phong.l), phong.n);
	phong.e = vec_normalize(subtract_tuples(cam, px));
	return (phong);
}

t_specs	_specs(float a, float d, float s, float ph)
{
	return ((t_specs){a, d, s, ph});
}

t_color	multiply_color_scalar(float scalar, t_color tup)
{
	t_color	res;

	res.r = scalar * tup.r;
	res.g = scalar * tup.g;
	res.b = scalar * tup.b;
	return (res);
}

t_color	rtn_phong(t_color a, t_color d)
{
	t_color	res;

	res.r = a.r + d.r;
	res.g = a.g + d.g;
	res.b = a.b + d.b;
	return (res);
}

//     return(illuminate(copms->obj, copms->point, world->light, copms->eyev, shadowed));

t_color	illuminate(t_comps *comps,t_light light, int in_shadow)
{
	t_phong		ph;
	float		light_dot_normal;

	if (!comps)
		return (_color(0, 0, 0));
	ph = _phong(comps->obj, comps->over_point, light, comps->eyev);
	if (in_shadow || compare_f(light.brightness , 0))
		return (ph.ambient);
	light_dot_normal = dot_product(ph.l, ph.n);
	if (light_dot_normal < 0 && comps->inside == 0)
		return (ph.ambient);
	else if (light_dot_normal < 0)
		light_dot_normal = -light_dot_normal;
	ph.diffuse = multiply_color_scalar(comps->obj->specs.diffuse * \
							light_dot_normal, ph.px_color);
	return (rtn_phong(ph.ambient, ph.diffuse));
}
