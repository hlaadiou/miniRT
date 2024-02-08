/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:35:57 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/02/08 17:47:16 by hlaadiou         ###   ########.fr       */
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

/* CROSS PRODUCT  (vec1 x vec2) */
t_vector	cross_product(t_vector vec1, t_vector vec2)
{
	t_vector	cross;

	cross.x = (vec1.y * vec2.z) - (vec1.z * vec2.y);
	cross.y = (vec1.z * vec2.x) - (vec1.x * vec2.z);
	cross.z = (vec1.x * vec2.y) - (vec1.y * vec2.x);
	return (cross);
}

/* DOT PRODUCT  (vec1 . vec2) */
t_vector	dot_product(t_vector vec1, t_vector vec2)
{
	t_vector	dot;

	dot.x = (vec1.y * vec2.z) - (vec1.z * vec2.y);
	dot.y = (vec1.z * vec2.x) - (vec1.x * vec2.z);
	dot.z = (vec1.x * vec2.y) - (vec1.y * vec2.x);
	return (dot);
}
