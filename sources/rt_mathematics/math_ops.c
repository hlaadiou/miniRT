/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:28:43 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/07/20 17:27:59 by azgaoua          ###   ########.fr       */
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
t_color	schur_product(t_color col1, t_color col2)
{
	t_color	blend;

	blend.r = col1.r * col2.r;
	blend.g = col1.g * col2.g;
	blend.b = col1.b * col2.b;
	return (blend);
}

/* DOT PRODUCT  (vec1 . vec2) */
float	dot_product(t_vector vec1, t_vector vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + \
				vec1.z * vec2.z + vec1.w * vec2.w);
}
