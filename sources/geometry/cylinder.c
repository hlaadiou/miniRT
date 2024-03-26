/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:03:30 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/03/26 07:10:33 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

//5 params
t_object	*_cylinder(t_point pt, t_vector axis, float d, float h, t_rgb255 *c)
{
	t_cylinder	*cy;

	cy = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cy)
		return (NULL);
	*cy = (t_cylinder){pt, axis, d, h, CYLINDER}; 
	return (_obj(cy, c, CYLINDER));
}
