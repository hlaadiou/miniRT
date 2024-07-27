/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:17:40 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/07/27 14:43:39 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pars.h"

/* counts the number of the chars in argument
while ignoring the leading zeros */
int	ft_real_len(char *str)
{
	size_t	count;
	size_t	index;

	index = 0;
	count = 0;
	if (str[0] == '-' || str[0] == '+')
	{
		count++;
		index++;
	}
	if (str[index] == '0')
	{
		while (str[index] == '0')
			index++;
		if (index == ft_strlen(str))
			return (++count);
	}
	while (str[index++])
		count++;
	return (count);
}

//Checks if the input is formatted as a correct number.
int	isnumber(char **str)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		if ((str[i][0] == '-' || str[i][0] == '+') && ft_strlen(str[i]) > 1)
			j++;
		while (str[i][j])
		{
			if (ft_isdigit(str[i][j]) == 1)
				j++;
			else
				return (0);
		}
		i++;
	}
	return (1);
}

//checks if the number passed is a valid integer.
int	is_int(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (ft_real_len(str[i]) >= 12)
			return (0);
		else if (ft_atoi(str[i]) < 0 || ft_atoi(str[i]) > INT_MAX)
			return (0);
		else
			i++;
	}
	return (1);
}

int	check_magnitude(char *str)
{
	if (fabsf(ft_atof(str)) > MAX_ABS_FLOAT)
	{
		ft_putstr_fd("Unsupported magnitude: Value exceeds maximum allowed magnitude of 1000!\n", 2);
		return (0);
	}
	return (1);
}

int	check_precision(char *str, size_t k)
{
	size_t	i;

	i = k;
	while (str[i] && str[i + 1])
		i++;
	while (str[i] == '0' && i >= k)
		i--;
	if ((i - k + 1) > 5)
	{
		ft_putstr_fd("Unsupported precision: The fractional part shouldn't exceed 5 digits!\n", 2);
		return (0);
	}
	return (1);
}

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