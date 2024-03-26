/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:02:55 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/03/26 10:17:45 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pars.h"

t_tuple	*parse_coordinates(char *str)
{
	int		i;
	char	**strs;
	t_tuple	*coords;

	i = -1;
	coords = NULL;
	strs = ft_split(str, ',');
	while (strs[++i])
		if (!valid_float(strs[i]))
			return (free_tab(strs), NULL);
	if (i != 3)
		return (free_tab(strs), NULL);
	coords = (t_tuple *)malloc(sizeof(t_tuple));
	if (!coords)
		return (free_tab(strs), NULL);
	*coords = (t_tuple){ft_atof(strs[0]), ft_atof(strs[1]), ft_atof(strs[2]), 0.0};
	return (free_tab(strs), coords);
}

t_rgb255	*parse_color(char *str)
{
	char		**strs;
	t_rgb255	*rgb;

	rgb = NULL;
	strs = ft_split(str, ',');
	if (ft_tab_size(strs) != 3 || !isnumber(strs) || !is_int(strs))
		return (free_tab(strs), NULL);
	rgb = (t_rgb255 *)malloc(sizeof(t_rgb255));
	if (!rgb)
		return (free_tab(strs), NULL);
	if (ft_atoi(strs[0]) < 0 || ft_atoi(strs[0]) > 255 \
		|| ft_atoi(strs[1]) < 0 || ft_atoi(strs[1]) > 255 \
		|| ft_atoi(strs[2]) < 0 || ft_atoi(strs[2]) > 255)
		return (free_tab(strs), NULL);
	*rgb = (t_rgb255){ft_atoi(strs[0]), ft_atoi(strs[1]), ft_atoi(strs[2])};
	return (rgb);
}

int	check_scene(t_scene *scene)
{
	if (!scene->ambient)
	{
		ft_putstr_fd("Error\nInvalid ambient lighting data\n", 2);
		return (0);
	}
	if (!scene->camera)
	{
		ft_putstr_fd("Error\nInvalid camera data\n", 2);
		return (free(scene->ambient), 0);
	}
	if (!scene->light)
	{
		ft_putstr_fd("Error\nInvalid light data\n", 2);
		return (free(scene->ambient), free(scene->camera), 0);
	}
	if (!scene->lst)
	{
		ft_putstr_fd("Error\nInvalid objects data\n", 2);
		return (free(scene->ambient), \
				free(scene->camera), free(scene->light), 0);
	}
	return (1);
}

t_scene	*parse_scene(t_pars *conf)
{
	t_scene		*scene;

	scene = NULL;
	if (!check_required_elements(conf))
		return (NULL);
	scene = (t_scene *)malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	scene->ambient = get_ambient_data(conf);
	scene->camera = get_camera_data(conf);
	scene->light = get_light_data(conf);
	scene->lst = get_objs_data(conf);
	if (!check_scene(scene))
		return (free(scene), NULL);
	return (scene);
}
