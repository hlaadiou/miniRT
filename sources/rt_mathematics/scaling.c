/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:39:06 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/03/01 10:57:41 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_matrix	*scaling_mtx(float x, float y, float z)
{
	t_matrix	*scale;

	scale = _identity(4);
	scale->mtx[0][0] = x;
	scale->mtx[1][1] = y;
	scale->mtx[2][2] = z;
	return (scale);
}
