/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:03:30 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/03/30 23:13:39 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

//5 params
t_object	*_cylinder(t_point pt, t_vector axis, float d, float h, t_color c)
{
	t_cylinder	*cy;

	cy = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cy)
		return (NULL);
	*cy = (t_cylinder){pt, axis, d, h, CYLINDER}; 
	return (_obj(cy, c, CYLINDER));
}
