/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:54:32 by azgaoua           #+#    #+#             */
/*   Updated: 2024/03/15 01:39:31 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*t1;
	unsigned char	*t2;

	t1 = (unsigned char *) s1;
	t2 = (unsigned char *) s2;
	i = 0;
	if (!s1 || !s2)
		return (0);
	while ((t1[i] != '\0' || t2[i] != '\0') && i < n)
	{
		if (t1[i] > t2[i])
			return (1);
		else if (t1[i] < t2[i])
			return (-1);
		i++;
	}
	return (0);
}

void	ft_pars(char *av, t_pars **pars)
{
	int	fd;
	char *line;

	fd = open(av, O_RDONLY);
	if (fd != -1)
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			if (line[0] == '#' || line[0] == '\n')
			{
				free(line);
				line = get_next_line(fd);
				continue;
			}
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
				while ((*pars) != NULL)
				{
					free_tab((*pars)->elements);
					free((*pars));
					(*pars) = (*pars)->next;
				}
				printf("Error\nwrong identifier\n");
				break ;
			}
			free(line);
			line = get_next_line(fd);
		}
	}
	close(fd);
	return ;
}

void print_lst(t_pars *pars)
{
	int  i;
	t_pars *tmp;

	i = 0;
	tmp = pars;
	while(tmp != NULL)
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
	if (ac == 2 && ft_strncmp(av[1] + ft_strlen(av[1]) - 3, ".rt", 3) == 0)
		ft_pars(av[1], &pars);
	else
		return (printf("bad extension\n"), 1);
	if (ft_lstsize(pars) < 4 && pars)
		return (printf("Error\nwrong number of identifiers\n"), 1);
	print_lst(pars);
}