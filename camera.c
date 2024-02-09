/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:03:50 by azgaoua           #+#    #+#             */
/*   Updated: 2024/02/09 16:11:59 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void camera(char *line, t_rt **rt)
{
	t_C	*camera;
	char	**tab;
	char	**tmp;

	camera = malloc(sizeof(t_C));
	tab = ft_split(line, ' ');
	tmp = ft_split(tab[1], ',');
	camera->coor[0] = ft_atoi(tmp[0]);
	camera->coor[1] = ft_atoi(tmp[1]);
	camera->coor[2] = ft_atoi(tmp[2]);
	free(tmp);
	tmp = ft_split(tab[2], ',');
	camera->nor_o_v[0] = ft_atoi(tmp[0]);
	camera->nor_o_v[1] = ft_atoi(tmp[1]);
	camera->nor_o_v[2] = ft_atoi(tmp[2]);
	free(tmp);
	camera->fov = ft_atoi(tab[3]);
	free(tab);
	(*rt)->C = camera;
}