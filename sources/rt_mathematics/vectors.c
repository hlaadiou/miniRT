/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:35:57 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/03/04 15:46:02 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/* GENERATES A TUPLE WITH A 0 W-COMPONENT */
t_vector	_vector(float x, float y, float z)
{
	t_tuple	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	vec.w = 0;
	return (vec);
}

/* SQUARED MODULUS */
float	squared_magnitude(t_vector vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
}

/* MODULUS */
float	vec_magnitude(t_vector vec)
{
	return (sqrt(squared_magnitude(vec)));
}

/* UNIT VECTOR OF AN ARBITRARY VEC */
t_vector	vec_normalize(t_vector vec)
{
	float		modulus;
	t_vector	unit_vec;

	modulus = vec_magnitude(vec);
	if (!modulus)
	{
		printf("U cannot normalize a vector of modulus 0\n");
		exit(EXIT_FAILURE);
	}
	unit_vec.x = vec.x / modulus;
	unit_vec.y = vec.y / modulus;
	unit_vec.z = vec.z / modulus;
	unit_vec.w = vec.w / modulus;
	return (unit_vec);
}

/* CROSS PRODUCT  (vec1 x vec2) */
t_vector	cross_product(t_vector vec1, t_vector vec2)
{
	t_vector	cross;

	cross.x = (vec1.y * vec2.z) - (vec1.z * vec2.y);
	cross.y = (vec1.z * vec2.x) - (vec1.x * vec2.z);
	cross.z = (vec1.x * vec2.y) - (vec1.y * vec2.x);
	cross.w = 0;
	return (cross);
}

/* DOT PRODUCT  (vec1 . vec2) */
float	dot_product(t_vector vec1, t_vector vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + \
				vec1.z * vec2.z + vec1.w * vec2.w);
}
