/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:19:01 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/03/02 15:47:19 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/*
 * a : ambient component
 * d : diffuse component
 * s : specular component
 * ph : phong coefficient (shininess)
*/

t_phong	_phong(t_object *obj, t_point px, t_light light, t_point cam)
{
	t_phong	phong;

	phong.n = normal_at(obj, px);
	phong.l = vec_normalize(subtract_tuples(light.position, px));
	phong.r = reflect(multiply_tuple_scalar(-1 , phong.l), phong.n);
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

t_color	illuminate(t_object *obj, t_point px, t_light light, t_point cam)
{
	t_phong		ph;
	t_color		px_color;
	t_color		ambient;
	t_color		diffuse;
	t_color		specular;
	float		light_dot_normal;
	float		reflect_dot_eye;
	float		factor;

	px_color = schur_product(_color((float)1, (float)0, (float)0), light.color);
	ph = _phong(obj, px, light, cam);
	ambient = multiply_color_scalar(obj->specs.ambient, px_color);
	light_dot_normal = dot_product(ph.l, ph.n);
	if (light_dot_normal < 0)
	{
		diffuse = _color(0, 0, 0);
		specular = _color(0, 0, 0);
	}
	else
	{
		diffuse = multiply_color_scalar(obj->specs.diffuse * light_dot_normal, px_color);
		reflect_dot_eye =  dot_product(ph.r, ph.e);
		if (reflect_dot_eye <= 0)
			specular = _color(0, 0, 0);
		else
		{
			factor = pow(reflect_dot_eye, obj->specs.phong_factor);
			specular = multiply_color_scalar(factor * obj->specs.specular, light.color);
		}
	}
	return (_color((ambient.r + diffuse.r + specular.r * 1), \
					ambient.g + diffuse.g + specular.g * 1,	\
				 	ambient.b + diffuse.b + specular.b * 1));
}
