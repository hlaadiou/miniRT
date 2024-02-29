/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:19:01 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/02/29 19:46:16 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lighting.h"

/*
 * a : ambient component
 * d : diffuse component
 * s : specular component
 * ph : phong coefficient (shininess)
 * */

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

t_color	illuminate(t_object *obj, t_point px, t_light light, t_point cam)
{
	t_phong		ph;
	t_color		px_color;

	ph = _phong(obj, px, light, cam);
	px_color = schur_product();
}
