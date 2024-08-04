/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_getters_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:58:13 by azgaoua           #+#    #+#             */
/*   Updated: 2024/07/27 18:08:27 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pars.h"
#include "../../includes/miniRT.h"

t_light_src	get_light_data(t_pars *conf)
{
	t_light_src	light;

	light = (t_light_src){0};
	while (conf)
	{
		if (conf->flag == LIGHT)
		{
			light = check_light_data(conf);
			break ;
		}
		conf = conf->next;
	}
	return (light);
}

t_object	*check_sp_data(t_pars *conf)
{
	t_object	*sp;
	t_point		pt;
	t_rgb255	rgb;

	sp = NULL;
	pt = parse_coordinates(conf->elements[1]);
	if (!valid_float(conf->elements[2]) || ft_atof(conf->elements[2]) < 0.0f)
		put_error("Invalid sphere diameter\n");
	rgb = parse_color(conf->elements[3]);
	pt.w = 1.0;
	sp = _sphere(pt, ft_atof(conf->elements[2]), _color01(rgb));
	if (!sp)
		put_error("Fatal, unable to create object\n");
	return (sp);
}

t_object	*check_pl_data(t_pars *conf)
{
	t_object	*pl;
	t_point		pt;
	t_vector	vec;
	t_rgb255	rgb;

	pl = NULL;
	pt = parse_coordinates(conf->elements[1]);
	vec = parse_coordinates(conf->elements[2]);
	if (!normalized_range(vec))
		put_error("The plane's orientation vector is not normalized\n");
	rgb = parse_color(conf->elements[3]);
	pl = _plane(pt, vec, _color01(rgb));
	if (!pl)
		put_error("Fatal, unable to create object\n");
	return (pl);
}

t_object	*check_cy_data(t_pars *conf)
{
	t_object	*cy;
	t_point		pt;
	t_vector	vec;
	t_rgb255	rgb;

	pt = parse_coordinates(conf->elements[1]);
	vec = parse_coordinates(conf->elements[2]);
	if (!normalized_range(vec))
		put_error("The cylinder's orientation vector is not normalized\n");
	if (!valid_float(conf->elements[3]) || !valid_float(conf->elements[4]) \
	|| ft_atof(conf->elements[3]) < 0.0f || ft_atof(conf->elements[4]) < 0.0f)
		put_error("Invalid cylinder diameter/height\n");
	rgb = parse_color(conf->elements[5]);
	cy = _cylinder(pt, vec, (t_attributes){ft_atof(conf->elements[3]), \
					(ft_atof(conf->elements[4]) / 2.0f), \
					(-1 * (ft_atof(conf->elements[4]) / 2.0f))}, _color01(rgb));
	if (!cy)
		put_error("Fatal, unable to create object\n");
	return (cy);
}

t_object	*check_objs_data(t_pars *conf)
{
	if (conf->flag == SP)
		return (check_sp_data(conf));
	else if (conf->flag == PL)
		return (check_pl_data(conf));
	else if (conf->flag == CY)
		return (check_cy_data(conf));
	else
		return (NULL);
}
