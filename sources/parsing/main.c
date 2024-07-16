/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:54:32 by azgaoua           #+#    #+#             */
/*   Updated: 2024/07/16 11:51:37 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

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

void ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_struct(t_pars *pars)
{
	t_pars	*tmp;

	while (pars)
	{
		tmp = pars;
		pars = pars->next;
		if (tmp->elements)
			ft_free_tab(tmp->elements);
		free(tmp);
	}
}

void	ft_pars(char *av, t_pars **pars)
{
	int		fd;
	char	*line = NULL;

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

// void	print_lst(t_pars *pars)
// {
// 	int		i;
// 	t_pars	*tmp;

// 	i = 0;
// 	tmp = pars;
// 	while (tmp != NULL)
// 	{
// 		printf("%d ", tmp->flag);
// 		i = 0;
// 		while (tmp->elements[i])
// 		{
// 			printf("%s ", tmp->elements[i]);
// 			i++;
// 		}
// 		printf("\n");
// 		tmp = tmp->next;
// 	}
// }

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
	printf("Color: %d %d %d\n", scene->ambient.color.r, scene->ambient.color.g, scene->ambient.color.b);
	printf("Ratio: %.2f\n\n", scene->ambient.scale);
	printf("Camera\n\n");
	printf("view_point: %.2f %.2f %.2f\n", scene->camera.view_point.x, scene->camera.view_point.y, scene->camera.view_point.z);
	printf("Orientation: %.2f %.2f %.2f\n", scene->camera.orientation.x, scene->camera.orientation.y, scene->camera.orientation.z);
	printf("FOV: %.2f\n\n", scene->camera.fov);
	printf("Light\n\n");
	printf("position: %.2f %.2f %.2f\n", scene->light.position.x, scene->light.position.y, scene->light.position.z);
	printf("Brightness: %.2f\n", scene->light.brightness);
	printf("Color: %d %d %d\n\n", scene->light.color.r, scene->light.color.g, scene->light.color.b);
	print_lstobj(scene->lst);
}

void	free_f_mtx(float **mtx, int size)
{
	while (size)
	{
		free(mtx[size - 1]);
		size--;
	}
	free(mtx);
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

// t_world	*init_world(t_scene *scene)
// {
// 	t_world	*world;

// 	world = malloc(sizeof(t_world));
// 	if (!world)
// 		return (NULL);
// 	world->light = scene->light;
// 	world->obj_lst = scene->lst;
// 	return (world);
// }

// t_comps *prepare_computations(t_inter *inter, t_ray ray)
// {
// 	t_comps	*comps;

// 	comps = malloc(sizeof(t_comps));
// 	if (!comps)
// 		return (NULL);
// 	comps->t = inter->t;
// 	comps->obj = inter->obj;
// 	comps->point = _position(ray, comps->t);
// 	comps->eyev = vec_normalize(multiply_tuple_scalar(-1, ray->dir));
// 	comps->normalv = normal_at(comps->obj, comps->point);
// 	if (dot_product(comps->normalv, comps->eyev) < 0)
// 	{
// 		comps->inside = 1;
// 		comps->normalv = multiply_tuple_scalar(-1, comps->normalv);
// 	}
// 	else
// 		comps->inside = 0;
// 	comps->over_point = add_tuples(comps->point, multiply_tuple_scalar(EPSILON, comps->normalv));
// 	return (comps);
// }

// int	main(int ac, char **av)
// {
// 	t_pars	*pars;
// 	t_scene	*scene;

// 	pars = NULL;
// 	if (ac != 2)
// 		return (ft_putstr_fd("Error\nWrong number of arguments\n", 2), 1);
// 	else if (ft_strncmp(av[1] + ft_strlen(av[1]) - 3, ".rt", 3) == 0 \
// 		&& av[1][0] != '.')
// 		ft_pars(av[1], &pars);
// 	else
// 		return (ft_putstr_fd("Error\nBad file name\n", 2), 1);
// 	if ((ft_lstsize(pars) < 4 && pars))
// 		return (ft_putstr_fd("Error\nWrong number of identifiers\n", 2), 1);
// 	scene = parse_scene(pars);
// 	if (!scene)
// 		return (1); //free
// 	// print_scene(scene);
// 	// world = init_world(scene);
// 	free_scene(scene);
// 	ft_free_struct(pars);
// 	return (0);
// }
