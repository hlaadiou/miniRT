/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:35:57 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/02/05 15:05:44 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_mathematics.h"

/* ADDITION  (vec1 + vec2) */
t_vector	add_vectors(t_vector vec1, t_vector vec2)
{
	t_vector	sum;

	sum.x = vec1.x + vec2.x;
	sum.y = vec1.y + vec2.y;
	sum.z = vec1.z + vec2.z;
	return (sum);
}

/* MULTIPLICATION BY SCALAR (a * vec2) */
t_vector	multiply_vector_scalar(double scalar, t_vector vec)
{
	vec.x = scalar * vec.x;
	vec.y = scalar * vec.y;
	vec.z = scalar * vec.z;
	return (vec);
}

/* SUBSTRACTION  (vec1 - vec2) */
t_vector	substract_vectors(t_vector vec1, t_vector vec2)
{
	t_vector	diff;

	diff = add_vectors(vec1, multiply_vector_scalar(-1, vec2));
	return (diff);
}

/* MULTIPLICATION  (vec1 * vec2) */
t_vector	multiply_vectors(t_vector vec1, t_vector vec2)
{
}

