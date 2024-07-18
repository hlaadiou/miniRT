/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_getters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:04:31 by hlaadiou          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/07/17 13:10:51 by hlaadiou         ###   ########.fr       */
=======
/*   Updated: 2024/07/18 16:40:57 by azgaoua          ###   ########.fr       */
>>>>>>> J-9
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
			ft_atof(conf->elements[1]) < 0.0 || ft_atof(conf->elements[1]) > 1.0)
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
	t_camera cam;

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
	if (!valid_float(conf->elements[2]))
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
	if (!valid_float(conf->elements[3]) || !valid_float(conf->elements[4]))
		put_error("Invalid cylinder diameter/height\n");
	rgb = parse_color(conf->elements[5]);
	cy = _cylinder(pt, vec, ft_atof(conf->elements[3]), \
					(ft_atof(conf->elements[4]) / 2.0f), (-1 * (ft_atof(conf->elements[4]) / 2.0f)), _color01(rgb)); /* to fix !! */
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

void	free_object(t_object *obj)
{
	if (obj->type == SPHERE)
		free(obj->sp);
	else if (obj->type == PLANE)
		free(obj->pl);
	else if (obj->type == CYLINDER)
		free(obj->cy);
	free_f_mtx(obj->transform->mtx, obj->transform->size);
	free(obj->transform);
	free(obj);
}

void	object_fatal(t_obj_lst *lst)
{
	t_obj_lst	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free_object(tmp->obj);
		free(tmp);
	}
	put_error("Fatal, Memory error: unable to create node\n");
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
				{
					// free_object(obj);
					// object_fatal(lst);
				}
			}
		}
		conf = conf->next;
	}
	return (lst);
}
