/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shearing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:42:31 by azgaoua           #+#    #+#             */
/*   Updated: 2024/02/18 16:10:05 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_mathematics.h"

/*
	6 parameters to much ...!!
*/

t_matrix	*shearing(float x_y, float x_z, float y_x, float y_z, float z_x, float z_y)
{
	t_matrix	*a;

	a = _identity(4);
	a->mtx[0][1] = x_y;
	a->mtx[0][2] = x_z;
	a->mtx[1][0] = y_x;
	a->mtx[1][2] = y_z;
	a->mtx[2][0] = z_x;
	a->mtx[2][1] = z_y;
	return (a);
}