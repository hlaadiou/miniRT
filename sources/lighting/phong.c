/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:19:01 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/03/01 12:00:19 by hlaadiou         ###   ########.fr       */
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
	phong.r = reflect(phong.l, phong.n);
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

	ph = _phong(obj, px, light, cam);
	px_color = schur_product(light.color, );
	ambient = multiply_color_scalar(obj->specs.ambient, px_color);
	light_dot_normal = dot_product(ph.l, ph.n);
	if (light_dot_normal < 0)
	{
		diffuse = _color(0, 0, 0);
		specular = _color(0, 0, 0);
	}
	else
	{
		diffuse;
		
		
	}

}
