/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:28:43 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/03/01 10:31:00 by hlaadiou         ###   ########.fr       */
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
