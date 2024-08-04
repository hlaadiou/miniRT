/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_validation_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:04:28 by azgaoua           #+#    #+#             */
/*   Updated: 2024/07/27 18:08:39 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pars.h"

int	valid_float(char *str)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	if ((str[i] == '-' || str[i] == '+') && str[i + 1])
	{
		i++;
		j++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == '.' && str[i + 1] && str[i + 1] != ' ' && i != j)
		i++;
	k = i;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (i == ft_strlen(str) && i != j)
	{
		if (!check_precision(str, k) || !check_magnitude(str))
			return (0);
		return (1);
	}
	return (0);
}
