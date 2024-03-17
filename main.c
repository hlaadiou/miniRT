/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:54:32 by azgaoua           #+#    #+#             */
/*   Updated: 2024/03/16 23:26:18 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"

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
		return (ft_putstr_fd("Error: wrong identifier\n", 2), 1);
	return (0);
}

void	ft_free_struct(t_pars **pars)
{
	while ((*pars) != NULL)
	{
		free_tab((*pars)->elements);
		free((*pars));
		(*pars) = (*pars)->next;
	}
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
				ft_free_struct(pars);
				break ;
			}
			free(line);
			line = get_next_line(fd);
		}
	}
	else
	{
		ft_putstr_fd("Error: cannot open file\n", 2);
		exit(0);
	}
	close(fd);
	return ;
}

void	print_lst(t_pars *pars)
{
	int		i;
	t_pars	*tmp;

	i = 0;
	tmp = pars;
	while (tmp != NULL)
	{
		printf("%d ", tmp->flag);
		i = 0;
		while (tmp->elements[i])
		{
			printf("%s ", tmp->elements[i]);
			i++;
		}
		printf("\n");
		tmp = tmp->next;
	}
}

int	main(int ac, char **av)
{
	t_pars	*pars;

	pars = NULL;
	if (ac != 2)
		return (ft_putstr_fd("Error: wrong number of arguments\n", 2), 0);
	else if (ft_strncmp(av[1] + ft_strlen(av[1]) - 3, ".rt", 3) == 0 \
		&& ft_strlen(av[1]) > 3)
		ft_pars(av[1], &pars);
	else
		return (ft_putstr_fd("Error: bad file name\n", 2), 0);
	if ((ft_lstsize(pars) < 4 && pars))
		return (ft_putstr_fd("Error: wrong number of identifiers\n", 2), 0);
	print_lst(pars);
}
