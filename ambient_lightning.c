/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_lightning.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:42:21 by azgaoua           #+#    #+#             */
/*   Updated: 2024/02/09 15:53:02 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ambient_lightning(char *line,t_rt **rt)
{
	t_A	*ambient_lightning;
	char	**tab;

	ambient_lightning = malloc(sizeof(t_A));
	tab = ft_split(line, ' ');
	if (tab[1][0] == '0' && tab[1][1] == '.')
		tab[1] = tab[1] + 2;
	ambient_lightning->ambient_l_r = ft_atoi(tab[1]);
	tab = ft_split(tab[2], ',');
	ambient_lightning->RGB[0] = ft_atoi(tab[0]);
	ambient_lightning->RGB[1] = ft_atoi(tab[1]);
	ambient_lightning->RGB[2] = ft_atoi(tab[2]);
	free(tab);
	(*rt)->A = ambient_lightning;
}
