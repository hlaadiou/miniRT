/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:28:43 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/02/17 13:30:00 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_mathematics.h"

// Returns 1 if a and b are "equal", 0 otherwise
int	compare_f(float a, float b)
{
	if (fabs(a - b) < EPSILON)
		return (1);
	else
		return (0);
}

// Element wise product
t_tuple	schur_product(t_tuple tup1, t_tuple tup2)
{
	t_tuple	prod;

	prod.x = tup1.x * tup2.x;
	prod.y = tup1.y * tup2.y;
	prod.z = tup1.z * tup2.z;
	prod.w = tup1.w * tup2.w;
	return (prod);
}
