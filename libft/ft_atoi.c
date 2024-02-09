/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 04:54:22 by azgaoua           #+#    #+#             */
/*   Updated: 2024/02/08 17:32:53 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoi(const char *str)
{
	int		i;
	long	retu;
	int		s;

	s = 1;
	i = 0;
	retu = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		retu = (retu * 10) + str[i] - 48;
		if (retu * s > 4294967295)
			return (-1);
		else if (retu * s < -4294967296)
			return (0);
		i++;
	}
	return ((int )(retu * s));
}
