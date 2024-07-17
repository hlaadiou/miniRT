/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:02:55 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/07/17 01:21:25 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pars.h"

int	ft_pars_loop(char *line, t_pars **pars)
{
	if (line[0] == '#' || line[0] == '\n' || line == NULL)
		return (0);
	else if (line[0] == 'A' && ft_strchr(" \t\r", line[1]) != NULL)
		ft_ambient(line, pars);
	else if (line[0] == 'C' && ft_strchr(" \t\r", line[1]) != NULL)
		ft_camera(line, pars);
	else if (line[0] == 'L' && ft_strchr(" \t\r", line[1]) != NULL)
		ft_light(line, pars);
	else if (line[0] == 's' && line[1] == 'p' && \
				ft_strchr(" \t\r", line[2]) != NULL)
		ft_pars_spher(line, pars);
	else if (line[0] == 'p' && line[1] == 'l' && \
				ft_strchr(" \t\r", line[2]) != NULL)
		plane_pars(line, pars);
	else if (line[0] == 'c' && line[1] == 'y' && \
				ft_strchr(" \t\r", line[2]) != NULL)
		cylinder_pars(line, pars);
	else
	{
		ft_putstr_fd("Error\nWrong identifier\n", 2);
		exit(1);
	}
	return (0);
}

void	ft_pars(char *av, t_pars **pars)
{
	int		fd;
	char	*line;

	fd = open(av, O_RDONLY);
	if (fd != -1)
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			if (ft_pars_loop(line, pars) == 1)
			{
				close(fd);
				break ;
			}
			free(line);
			line = get_next_line(fd);
		}
	}
	else
	{
		ft_putstr_fd("Error\nCannot open file\n", 2);
		exit(1);
	}
	close(fd);
	return ;
}

void print_lstobj(t_obj_lst *lst)
{
	t_obj_lst	*tmp;
	tmp = lst;
	while (tmp)
	{
		if (tmp->obj->type == SPHERE)
		{
			printf("Sphere\n\n");
			printf("Center: %.2f %.2f %.2f\n", tmp->obj->sp->org.x, tmp->obj->sp->org.y, tmp->obj->sp->org.z);
			printf("Radius: %.2f\n", tmp->obj->sp->radius);
			printf("Color: %.2f %.2f %.2f\n\n", tmp->obj->color.r, tmp->obj->color.g, tmp->obj->color.b);
		}
		else if (tmp->obj->type == PLANE)
		{
			printf("Plane\n\n");
			printf("Point: %.2f %.2f %.2f\n", tmp->obj->pl->pt.x, tmp->obj->pl->pt.y, tmp->obj->pl->pt.z);
			printf("Vector: %.2f %.2f %.2f\n", tmp->obj->pl->vec.x, tmp->obj->pl->vec.y, tmp->obj->pl->vec.z);
			printf("Color: %.2f %.2f %.2f\n\n", tmp->obj->color.r, tmp->obj->color.g, tmp->obj->color.b);
		}
		else if (tmp->obj->type == CYLINDER)
		{
			printf("Cylinder\n\n");
			printf("Center: %.2f %.2f %.2f\n", tmp->obj->cy->center.x, tmp->obj->cy->center.y, tmp->obj->cy->center.z);
			printf("Axis: %.2f %.2f %.2f\n", tmp->obj->cy->axis.x, tmp->obj->cy->axis.y, tmp->obj->cy->axis.z);
			printf("Diameter: %.2f\n", tmp->obj->cy->diameter);
			printf("Height: %.2f\n", fabs(tmp->obj->cy->max - tmp->obj->cy->min));
			printf("Color: %.2f %.2f %.2f\n\n", tmp->obj->color.r, tmp->obj->color.g, tmp->obj->color.b);
		}
		tmp = tmp->next;
	}
}

void print_scene(t_scene *scene)
{
	printf("Ambient\n\n");
	printf("Color: %f %f %f\n", scene->ambient.color.r, scene->ambient.color.g, scene->ambient.color.b);
	printf("Ratio: %.2f\n\n", scene->ambient.scale);
	printf("Camera\n\n");
	printf("view_point: %.2f %.2f %.2f\n", scene->camera.view_point.x, scene->camera.view_point.y, scene->camera.view_point.z);
	printf("Orientation: %.2f %.2f %.2f\n", scene->camera.orientation.x, scene->camera.orientation.y, scene->camera.orientation.z);
	printf("FOV: %.2f\n\n", scene->camera.fov);
	printf("Light\n\n");
	printf("position: %f %f %f\n", scene->light.position.x, scene->light.position.y, scene->light.position.z);
	printf("Brightness: %.2f\n", scene->light.brightness);
	printf("Color: %f %f %f\n\n", scene->light.color.r, scene->light.color.g, scene->light.color.b);
	print_lstobj(scene->lst);
}

void	free_obj_lst(t_obj_lst *lst)
{
	t_obj_lst	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		if (tmp->obj->type == SPHERE)
		{
			free(tmp->obj->sp);
		}
		else if (tmp->obj->type == PLANE)
		{
			free(tmp->obj->pl);
		}
		else if (tmp->obj->type == CYLINDER)
		{
			free(tmp->obj->cy);
		}
		free_f_mtx(tmp->obj->transform->mtx, tmp->obj->transform->size);
		free(tmp->obj->transform);
		free(tmp->obj);
		free(tmp);
	}
}

void free_scene(t_scene *scene)
{
	free_obj_lst(scene->lst);
	free(scene);
}

t_pars	*create_conf(int ac, char **av)
{
	t_pars	*pars;

	pars = NULL;
	if (ac != 2)
		return (ft_putstr_fd("Error\nWrong number of arguments\n", 2), NULL);
	else if (ft_strncmp(av[1] + ft_strlen(av[1]) - 3, ".rt", 3) == 0 \
														&& av[1][0] != '.')
		ft_pars(av[1], &pars);
	else
		return (ft_putstr_fd("Error\nBad file name\n", 2), NULL);
	if ((ft_lstsize(pars) < 4 && pars))
		return (ft_putstr_fd("Error\nWrong number of identifiers\n", 2), NULL);
	return (pars);
}

void	put_error(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

int	multiple_sep(char *str, char c)
{
	int	i;
	int count;

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
		{
			// free_tab(strs);
			put_error("Invalid coordinates data\n");
		}
	}
	if (i != 3)
	{
		// free_tab(strs);
		put_error("Invalid coordinates data\n");
	}
	coords = (t_tuple){ft_atof(strs[0]), ft_atof(strs[1]), ft_atof(strs[2]), 0.0};
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
	{
		// free_tab(strs);
		put_error("Invalid color data\n");
	}
	if (ft_atoi(strs[0]) < 0 || ft_atoi(strs[0]) > 255 \
	|| ft_atoi(strs[1]) < 0 || ft_atoi(strs[1]) > 255 \
	|| ft_atoi(strs[2]) < 0 || ft_atoi(strs[2]) > 255)
	{
		// free_tab(strs);
		put_error("Invalid color data\n");
	}
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
