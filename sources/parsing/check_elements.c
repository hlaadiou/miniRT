/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:34:52 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/03/26 09:39:12 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pars.h"

int	check_al(t_pars *conf)
{
	int	counter;

	counter = 0;
	while (conf)
	{
		if (conf->flag == 1)
			counter++;
		conf = conf->next;
	}
	if (!counter)
		return (ft_putstr_fd("Error\nAmbient lighting not defined\n", 2), 0);
	else if (counter > 1)
		return (ft_putstr_fd("Error\nAmbient lighting defined many times\n", 2), 0);
	else
		return (1);
}

int	check_camera(t_pars *conf)
{
	int	counter;

	counter = 0;
	while (conf)
	{
		if (conf->flag == 2)
			counter++;
		conf = conf->next;
	}
	if (!counter)
		return (ft_putstr_fd("Error\nCamera not defined\n", 2), 0);
	else if (counter > 1)
		return (ft_putstr_fd("Error\nCamera defined more than once\n", 2), 0);
	else
		return (1);
}

int	check_light(t_pars *conf)
{
	int	counter;

	counter = 0;
	while (conf)
	{
		if (conf->flag == 3)
			counter++;
		conf = conf->next;
	}
	if (!counter)
		return (ft_putstr_fd("Error\nLight not defined\n", 2), 0);
	else if (counter > 1)
		return (ft_putstr_fd("Error\nLight defined more than once\n", 2), 0);
	else
		return (1);
}

/* Returns the nb of objects in the scene, 0 with error message otherwise */
int	check_objects(t_pars *conf)
{
	int	counter;

	counter = 0;
	while (conf)
	{
		if (conf->flag > 3)
			counter++;
		conf = conf->next;
	}
	if (!counter)
		return (ft_putstr_fd("Error\nScene should contain at least one object\n", 2), 0);
	else
		return (counter);
}

int	check_required_elements(t_pars *conf)
{
	if (!check_al(conf) || !check_camera(conf) || !check_light(conf) \
		|| !check_objects(conf))
		return (0);
	return (1);
}
