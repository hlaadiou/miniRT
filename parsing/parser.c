/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:02:55 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/03/24 18:28:37 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"

t_tuple	*parse_coordinates(char *str)
{
	int		i;
	char	**strs;
	t_tuple	*coords;

	i = -1;
	coords = NULL;
	strs = ft_split(str, ',');
	while (strs[++i])
		if (!valid_float(strs[i]))
			return (free_tab(strs), NULL);
	if (i != 3)
		return (free_tab(strs), NULL);
	coords = (t_tuple *)malloc(sizeof(t_tuple));
	if (!coords)
		return (free_tab(strs), NULL);
	*coords = (t_tuple){ft_atof(strs[0]), ft_atof(strs[1]), ft_atof(strs[2]), 0.0};
	return (free_tab(strs), coords);
}

t_rgb255	*parse_color(char *str)
{
	char		**strs;
	t_rgb255	*rgb;

	rgb = NULL;
	strs = ft_split(str, ',');
	if (ft_tab_size(strs) != 3 || !isnumber(strs) || !is_int(strs))
		return (free_tab(strs), NULL);
	rgb = (t_rgb255 *)malloc(sizeof(t_rgb255));
	if (!rgb)
		return (free_tab(strs), NULL);
	*rgb = (t_rgb255){ft_atoi(strs[0]), ft_atoi(strs[1]), ft_atoi(strs[2])};
	return (rgb);
}

t_scene	*parse_scene(t_pars *conf)
{
}
