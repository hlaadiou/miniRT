/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:28:05 by azgaoua           #+#    #+#             */
/*   Updated: 2024/03/01 10:57:28 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// r(RADIANS)
t_matrix	*rotation_x(float r)
{
	t_matrix *a;

	a = _identity(4);
	a->mtx[1][1] = cos(r);
	a->mtx[2][2] = cos(r);
	a->mtx[2][1] = sin(r);
	a->mtx[1][2] = sin(r) * (-1);
	return (a);
}

t_matrix	*rotation_y(float r)
{
	t_matrix *a;
	a = _identity(4);
	a->mtx[0][0] = cos(r);
	a->mtx[0][2] = sin(r);
	a->mtx[2][0] = sin(r) * (-1);
	a->mtx[2][2] = cos(r);
	return (a);
}

t_matrix	*rotation_z(float r)
{
	t_matrix *a;

	a = _identity(4);
	a->mtx[0][0] = cos(r);
	a->mtx[0][1] = sin(r) * (-1);
	a->mtx[1][0] = sin(r);
	a->mtx[1][1] = cos(r);
	return (a);
}
