/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:39:06 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/02/18 16:10:05 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_mathematics.h"

t_matrix	*scaling_mtx(float x, float y, float z)
{
	t_matrix	*scale;

	scale = _identity(4);
	scale->mtx[0][0] = x;
	scale->mtx[1][1] = y;
	scale->mtx[2][2] = z;
	return (scale);
}
