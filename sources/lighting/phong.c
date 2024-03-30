/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:19:01 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/03/27 08:21:44 by azgaoua          ###   ########.fr       */
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
	phong.n = normal_at(obj, px);
	phong.l = vec_normalize(subtract_tuples(light.position, px));
	phong.r = reflect(multiply_tuple_scalar(-1, phong.l), phong.n);
	phong.e = vec_normalize(subtract_tuples(cam, px));
	return (phong);
}

t_specs	_specs(float a, float d, float s, float ph)
{
	return ((t_specs){a, d, s, ph});
}

t_rgb255	*multiply_color_scalar(float scalar, t_rgb255 *tup)
{
	t_rgb255	*res;

	res = (t_rgb255 *)malloc(sizeof(t_rgb255));
	res->r = scalar * (*tup).r;
	res->g = scalar * (*tup).g;
	res->b = scalar * (*tup).b;
	return (res);
}

t_rgb255	*rtn_phong(t_rgb255 *a, t_rgb255 *d, t_rgb255 *s)
{
	t_rgb255	*res;

	res = (t_rgb255 *)malloc(sizeof(t_rgb255));
	res->r = (*a).r + (*d).r + (*s).r;
	res->g = (*a).g + (*d).g + (*s).g;
	res->b = (*a).b + (*d).b + (*s).b;
	return (res);
}

t_rgb255	*illuminate(t_object *obj, t_point px, t_light light, t_point cam)
{
	t_phong		ph;
	float		light_dot_normal;
	float		reflect_dot_eye;
	float		factor;

	ph = _phong(obj, px, light, cam);
	light_dot_normal = dot_product(ph.l, ph.n);
	if (light_dot_normal >= 0)
	{
		ph.diffuse = multiply_color_scalar(obj->specs.diffuse * \
								light_dot_normal, ph.px_color);
		reflect_dot_eye = dot_product(ph.r, ph.e);
		if (reflect_dot_eye > 0)
		{
			factor = pow(reflect_dot_eye, obj->specs.phong_factor);
			ph.specular = multiply_color_scalar(factor * \
									obj->specs.specular, light.color);
		}
	}
	return (rtn_phong(ph.ambient, ph.diffuse, ph.specular));
}
