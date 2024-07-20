/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_getters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:04:31 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/07/20 17:03:11 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pars.h"
#include "../../includes/lighting.h"

t_ambient	get_ambient_data(t_pars *conf)
{
	t_ambient	amb;
	t_rgb255	rgb;

	amb = (t_ambient){0};
	while (conf)
	{
		if (conf->flag == AMB)
		{
			if (!valid_float(conf->elements[1]) || \
			ft_atof(conf->elements[1]) < 0.0 || \
					ft_atof(conf->elements[1]) > 1.0)
				put_error("Invalid ambient lighting ratio\n");
			rgb = parse_color(conf->elements[2]);
			amb.scale = ft_atof(conf->elements[1]);
			amb.color = _color01(rgb);
			break ;
		}
		conf = conf->next;
	}
	return (amb);
}

int	normalized_range(t_vector vec)
{
	if (vec.x < -1.0 || vec.x > 1.0 \
		|| vec.y < -1.0 || vec.y > 1.0 \
		|| vec.z < -1.0 || vec.z > 1.0)
		return (0);
	return (1);
}

t_camera	check_camera_data(t_pars *conf)
{
	t_camera	cam;
	t_point		pt;
	t_vector	vec;

	pt = parse_coordinates(conf->elements[1]);
	vec = parse_coordinates(conf->elements[2]);
	if (!normalized_range(vec))
		put_error("The camera's orientation vector is not normalized\n");
	if (!valid_float(conf->elements[3]) || \
	ft_atof(conf->elements[3]) < 0.0 || ft_atof(conf->elements[3]) > 180.0)
		put_error("The camera's FOV range is invalid\n");
	pt.w = 1.0;
	cam = (t_camera){pt, vec, ft_atof(conf->elements[3])};
	return (cam);
}

t_camera	get_camera_data(t_pars *conf)
{
	t_camera	cam;

	cam = (t_camera){0};
	while (conf)
	{
		if (conf->flag == CAM)
		{
			cam = check_camera_data(conf);
			break ;
		}
		conf = conf->next;
	}
	return (cam);
}

t_light_src	check_light_data(t_pars *conf)
{
	t_light_src	light;
	t_point		pt;
	t_rgb255	rgb;

	pt = parse_coordinates(conf->elements[1]);
	if (!valid_float(conf->elements[2]) || ft_atof(conf->elements[2]) < 0.0 \
			|| ft_atof(conf->elements[2]) > 1.0)
		put_error("Invalid light brightness\n");
	rgb = parse_color(conf->elements[3]);
	pt.w = 1.0;
	light = (t_light_src){pt, ft_atof(conf->elements[2]), _color01(rgb)};
	return (light);
}
