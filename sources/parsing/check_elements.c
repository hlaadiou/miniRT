/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:34:52 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/07/31 20:02:51 by azgaoua          ###   ########.fr       */
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
		return (put_error("Ambient lighting not defined\n"), 0);
	else if (counter > 1)
		return (put_error("Ambient lighting defined many times\n"), 0);
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
		return (put_error("Camera not defined\n"), 0);
	else if (counter > 1)
		return (put_error("Camera defined more than once\n"), 0);
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
		return (put_error("Light not defined\n"), 0);
	else if (counter > 1)
		return (put_error("Light defined more than once\n"), 0);
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
		return (put_error \
				("Scene should contain at least one object\n"), 0);
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
