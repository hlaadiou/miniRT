/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:39:06 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/02/17 15:40:22 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_mathematics.h"

t_matrix	*scaling_mtx(float x, float y, float z)
{
	t_matrix	*scale;

	scale = identity_mtx(4);
	scale->mtx[0][0] = x;
	scale->mtx[1][1] = y;
	scale->mtx[2][2] = z;
	return (scale);
}
