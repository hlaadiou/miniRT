/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:02:55 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/07/31 20:18:07 by azgaoua          ###   ########.fr       */
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
		return (1);
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
				free(line);
				put_error("Wrong identifier\n");
			}
			free(line);
			line = get_next_line(fd);
		}
	}
	else
		put_error("Cannot open file\n");
	close(fd);
	return ;
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

void	free_scene(t_scene *scene)
{
	free_obj_lst(scene->lst);
	free(scene);
}

t_pars	*create_conf(int ac, char **av)
{
	t_pars	*pars;

	pars = NULL;
	if (ac != 2)
		return (put_error("Wrong number of arguments\n"), NULL);
	else if (ft_strncmp(av[1] + ft_strlen(av[1]) - 3, ".rt", 3) == 0 \
														&& av[1][0] != '.')
		ft_pars(av[1], &pars);
	else
		return (put_error("Bad file name\n"), NULL);
	if ((ft_lstsize(pars) < 4 && pars))
		return (put_error("Wrong number of identifiers\n"), NULL);
	return (pars);
}
