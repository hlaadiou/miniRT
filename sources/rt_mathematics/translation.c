/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:21:00 by azgaoua           #+#    #+#             */
/*   Updated: 2024/02/18 16:10:05 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_mathematics.h"

t_matrix *translation(float x, float y, float z)
{
	t_matrix *a;

	a = _identity(4);
	a->mtx[0][3] = x;
	a->mtx[1][3] = y;
	a->mtx[2][3] = z;
	return (a);
}