/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_getters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:04:31 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/03/27 00:26:42 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pars.h"

t_ambient	*get_ambient_data(t_pars *conf)
{
	t_ambient	*amb;
	t_rgb255	*rgb;

	amb = NULL;
	while (conf)
	{
		if (conf->flag == AMB)
		{
			if (!valid_float(conf->elements[1]))
				return (NULL);
			rgb = parse_color(conf->elements[2]);
			if (!rgb)
				return (NULL);
			amb = (t_ambient*)malloc(sizeof(t_ambient));
			if (!amb)
				return (NULL);
			amb->scale = ft_atof(conf->elements[1]);
			amb->color = rgb;
			break ;
		}
		conf = conf->next;
	}
	return (amb);
}

int	normalized_range(t_vector *vec)
{
	if (vec->x < -1.0 || vec->x > 1.0 \
		|| vec->y < -1.0 || vec->y > 1.0 \
		|| vec->z < -1.0 || vec->z > 1.0)
		return (0);
	return (1);
}

t_camera	*check_camera_data(t_pars *conf)
{
	t_camera	*cam;
	t_point		*pt;
	t_vector	*vec;

	cam = NULL;
	pt = parse_coordinates(conf->elements[1]);
	if (!pt)
		return (NULL);
	vec = parse_coordinates(conf->elements[2]);
	if (!vec)
		return (free(pt), NULL);
	if (!normalized_range(vec))
		return (free(pt), free(vec), NULL);
	if (!valid_float(conf->elements[3]) || \
	ft_atof(conf->elements[3]) < 0.0 || ft_atof(conf->elements[3]) > 180.0)
		return (free(pt), free(vec), NULL);
	cam = (t_camera*)malloc(sizeof(t_camera));
	if (!cam)
		return (free(pt), free(vec), NULL);
	pt->w = 1.0;
	*cam = (t_camera){pt, vec, ft_atof(conf->elements[3])};
	return (cam);
}

t_camera	*get_camera_data(t_pars *conf)
{
	t_camera	*cam;

	cam = NULL;
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

t_light_src	*check_light_data(t_pars *conf)
{
	t_light_src	*light;
	t_point		*pt;
	t_rgb255	*rgb;

	light = NULL;
	pt = parse_coordinates(conf->elements[1]);
	if (!pt)
		return (NULL);
	if (!valid_float(conf->elements[2]) || ft_atof(conf->elements[2]) < 0.0 \
			|| ft_atof(conf->elements[2]) > 1.0)
		return (free(pt), NULL);
	rgb = parse_color(conf->elements[3]);
	if (!rgb)
		return (free(pt), NULL);
	light = (t_light_src*)malloc(sizeof(t_light_src));
	if (!light)
		return (free(pt), free(rgb), NULL);
	pt->w = 1.0;
	*light = (t_light_src){pt, ft_atof(conf->elements[2]), rgb};
	return (light);
}

t_light_src	*get_light_data(t_pars *conf)
{
	t_light_src	*light;

	light = NULL;
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
	t_point		*pt;
	t_rgb255	*rgb;

	sp = NULL;
	pt = parse_coordinates(conf->elements[1]);
	if (!pt)
		return (NULL);
	if (!valid_float(conf->elements[2]))
		return (free(pt), NULL);
	rgb = parse_color(conf->elements[3]);
	if (!rgb)
		return (free(pt), NULL);
	pt->w = 1.0;
	sp = _sphere(*pt, ft_atof(conf->elements[2]), rgb);
	if (!sp)
		return (free(pt), free(rgb), NULL);
	return (sp);
}

t_object	*check_pl_data(t_pars *conf)
{
	t_object	*pl;
	t_point		*pt;
	t_vector	*vec;
	t_rgb255	*rgb;

	pl = NULL;
	pt = parse_coordinates(conf->elements[1]);
	if (!pt)
		return (NULL);
	vec = parse_coordinates(conf->elements[2]);
	if (!vec)
		return (free(pt), NULL);
	if (!normalized_range(vec))
		return (free(pt), free(vec), NULL);
	rgb = parse_color(conf->elements[3]);
	if (!rgb)
		return (free(pt), free(vec), NULL);
	pl = _plane(*pt, *vec, rgb);
	if (!pl)
		return (free(pt), free(vec), free(rgb), NULL);
	return (pl);
}

t_object	*check_cy_data(t_pars *conf)
{
	t_object	*cy;
	t_point		*pt;
	t_vector	*vec;
	t_rgb255	*rgb;

	cy = NULL;
	pt = parse_coordinates(conf->elements[1]);
	if (!pt)
		return (NULL);
	vec = parse_coordinates(conf->elements[2]);
	if (!vec)
		return (free(pt), NULL);
	if (!normalized_range(vec))
		return (free(pt), free(vec), NULL);
	if (!valid_float(conf->elements[3]) || !valid_float(conf->elements[4]))
		return (free(pt), free(vec), NULL);
	rgb = parse_color(conf->elements[5]);
	if (!rgb)
		return (free(pt), free(vec), NULL);
	cy = _cylinder(*pt, *vec, ft_atof(conf->elements[3]), \
	ft_atof(conf->elements[4]), rgb);
	if (!cy)
		return (free(pt), free(vec), free(rgb), NULL);
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

t_obj_lst	*get_objs_data(t_pars *conf)
{
	t_obj_lst	*lst;
	t_object	*obj;

	lst = NULL;
	obj = NULL;
	while (conf)
	{
		if (conf->flag == SP || conf->flag == PL || conf->flag == CY)
		{
			obj = check_objs_data(conf);
			if (obj)
			{
				if (obj_list_add(&lst, obj))
					return (free(obj), NULL); //SHOULD FREE LIST
			}
			else
				return (free(obj), NULL);
		}
		conf = conf->next;
	}
	return (lst);
}
