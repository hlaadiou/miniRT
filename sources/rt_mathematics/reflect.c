/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:41:07 by azgaoua           #+#    #+#             */
/*   Updated: 2024/02/23 16:20:51 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/geometry.h"
#include "../../includes/rt_mathematics.h"

t_vector	reflect(t_vector a, t_vector n)
{
	return (subtract_tuples(a, \
			multiply_tuple_scalar((2 * dot_product(a, n)), n)));
}

// int main(void)
// {
// 	t_vector v = _vector(0, -1, 0);
// 	t_vector n = _vector(sqrt(2)/2, sqrt(2)/2, 0);
// 	t_vector r = reflect(v, n);

// 	printf("r (%.2f, %.2f, %.2f)\n", r.x, r.y, r.z);
// 	return 0;
// }