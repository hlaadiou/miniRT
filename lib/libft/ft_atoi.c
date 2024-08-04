/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 04:54:22 by azgaoua           #+#    #+#             */
/*   Updated: 2024/07/31 18:50:41 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoi(const char *str)
{
	int			i;
	long long	retu;
	int			s;

	s = 1;
	i = 0;
	retu = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			s = -1;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		while (str[i] == ' ')
			i++;
		retu = (retu * 10) + str[i++] - 48;
		if (retu * s > 4294967295)
			return (4294967296);
		else if (retu * s < -4294967296)
			return (4294967296);
	}
	return ((retu * s));
}
