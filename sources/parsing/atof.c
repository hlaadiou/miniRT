/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:20:27 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/07/16 22:12:10 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pars.h"

int	ft_check_sign(char *str, float *sign, int index)
{
	*sign = 1.0;
	if (str[index] == '-')
	{
		*sign *= -1.0;
		index++;
	}
	else if (str[index] == '+')
		index++;
	return (index);
}

float	ft_atof(char *str)
{
	t_float	nb;
	int		i;

	i = 0;
	nb.whole = 0.0;
	nb.decimal = 1.0;
	i = ft_check_sign(str, &nb.sign, i);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nb.whole = nb.whole * 10 + str[i] - '0';
		i++;
	}
	if (str[i] == '.')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nb.decimal /= 10;
		nb.whole += nb.decimal * (str[i] - '0');
		i++;
	}
	return (nb.whole * nb.sign);
}
