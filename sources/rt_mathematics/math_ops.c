/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:28:43 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/03/27 07:59:30 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// Returns 1 if a and b are "equal", 0 otherwise
int	compare_f(float a, float b)
{
	if (fabs(a - b) < EPSILON)
		return (1);
	else
		return (0);
}

// Element wise product
t_rgb255	*schur_product(t_rgb255 *col1, t_rgb255 *col2)
{
	t_rgb255	*blend;

	blend = (t_rgb255 *)malloc(sizeof(t_rgb255));
	blend->r = (*col1).r * (*col2).r;
	blend->g = (*col1).g * (*col2).g;
	blend->b = (*col1).b * (*col2).b;
	return (blend);
}
