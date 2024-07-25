/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:17:27 by azgaoua           #+#    #+#             */
/*   Updated: 2024/07/25 16:14:49 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pars.h"

void	put_error(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

int	multiple_sep(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	if (count != 2)
		return (1);
	return (0);
}

t_tuple	parse_coordinates(char *str)
{
	int		i;
	char	**strs;
	t_tuple	coords;

	i = -1;
	if (multiple_sep(str, ','))
		put_error("Invalid coordinates format\n");
	strs = ft_split(str, ',');
	while (strs[++i])
	{
		if (!valid_float(strs[i]))
			put_error("Invalid coordinates data\n");
	}
	if (i != 3)
		put_error("Invalid coordinates data\n");
	coords = (t_tuple){ft_atof(strs[0]), ft_atof(strs[1]), \
				ft_atof(strs[2]), 0.0};
	return (coords);
}

t_rgb255	parse_color(char *str)
{
	char		**strs;
	t_rgb255	rgb;

	if (multiple_sep(str, ','))
		put_error("Invalid color format\n");
	strs = ft_split(str, ',');
	if (ft_tab_size(strs) != 3 || !isnumber(strs) || !is_int(strs))
		put_error("Invalid color data\n");
	if (ft_atoi(strs[0]) < 0 || ft_atoi(strs[0]) > 255 \
	|| ft_atoi(strs[1]) < 0 || ft_atoi(strs[1]) > 255 \
	|| ft_atoi(strs[2]) < 0 || ft_atoi(strs[2]) > 255)
		put_error("Invalid color data\n");
	rgb = (t_rgb255){ft_atoi(strs[0]), ft_atoi(strs[1]), ft_atoi(strs[2])};
	return (rgb);
}

// t_pars needs to freed in case of error as well as object list and scene
t_scene	*parse_scene(t_pars *conf)
{
	t_scene		*scene;

	scene = NULL;
	if (!check_required_elements(conf))
		return (NULL);
	scene = (t_scene *)ft_malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	
	scene->ambient = get_ambient_data(conf);
	scene->camera = get_camera_data(conf);
	scene->light = get_light_data(conf);
	scene->lst = get_objs_data(conf);
	return (scene);
}
