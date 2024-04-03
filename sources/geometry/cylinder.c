/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:03:30 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/04/02 00:39:36 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

//5 params
// typedef struct s_cylinder
// {
// 	t_point		center;
// 	t_vector	axis;
// 	float		diameter;
// 	float		min;
// 	float		max;
// }	t_cylinder;
t_object	*_cylinder(t_point pt, t_vector axis, float d, float max,float min, t_color c)
{
	t_cylinder	*cy;

	cy = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cy)
		return (NULL);
	*cy = (t_cylinder){pt, axis, d, min, max};
	return (_obj(cy, c, CYLINDER));
}
