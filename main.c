/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:31:15 by azgaoua           #+#    #+#             */
/*   Updated: 2024/02/09 16:01:34 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void parser(char *av, t_rt **rt)
{
	int		fd;
	char	*line;

	fd = open(av, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == 'A' && line[1] == ' ')
			ambient_lightning(line, rt);
		// else if (line[0] == 'C' && line[1] == ' ')
		// 	camera(line, rt);
		// else if (line[0] == 'L' && line[1] == ' ')
		// 	light(line, rt);
		// else if (line[0] == 's' && line[1] == 'p' && line[2] == ' ')
		// 	sphere(line, rt);
		// else if (line[0] == 'p' && line[1] == 'l' && line[2] == ' ')
		// 	plane(line, rt);
		// else if (line[0] == 'c' && line[1] == 'y' && line[2] == ' ')
		// 	cylinder(line, rt);
		
		// printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

int	main(int ac, char **av)
{
	t_rt	*rt;

	if (ac != 2 || (!ft_strncmp(av[1], \
					".rt", ft_strlen_gnl(av[1]) - 4)) || \
			open_tests(av))
	{
		if (!ft_strncmp(av[1], ".rt", ft_strlen_gnl(av[1]) - 4))
			return (ft_putstr_fd("the file should end with \".rt\"\n", 2), 0);
		else if (ac != 2)
			return (ft_putstr_fd("usage: ./miniRT file.rt\n", 2), 0);
	}
	else
	{
		rt = malloc(sizeof(t_rt));
		parser(av[1], &rt);
		printf("%d ", rt->A->ambient_l_r);
		printf("%d,", rt->A->RGB[0]);
		printf("%d,", rt->A->RGB[1]);
		printf("%d\n", rt->A->RGB[2]);
	}
	return (0);
}
