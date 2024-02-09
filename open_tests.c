/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:33:39 by azgaoua           #+#    #+#             */
/*   Updated: 2024/02/08 21:18:05 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int open_tests(char **av)
{
	int fd;

	fd = open(av[1], O_RDONLY);

	if (fd == -1)
		return (perror("file not found"), 1);
	
	close(fd);
	return (0);
}
