/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:58:11 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/02/18 15:21:24 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRY_H
# define GEOMETRY_H

# include "rt_mathematics.h"

/*
 * USER DEFINED DATA TYPES
 */

typedef struct s_ray
{
	t_point		org;
	t_vector	dir;
}	t_ray;

typedef struct s_intersection
{
	float	t1;
	float	t2;
	int		counter;
}	t_intersection;

typedef struct s_quadratic
{
	float	a;
	float	b;
	float	c;
	float	delta;
}	t_quadratic;

/*
 * GEOMETRIC SHAPES
 */

typedef struct s_sphere
{
	t_point	org;
	float	radius;
}	t_sphere;

typedef struct s_cylinder
{
}	t_cylinder;

typedef struct s_plane
{
}	t_plane;

/*
 * FUNCTIONS PROTOTYPES
 */

t_ray			_ray(t_point org, t_vector vec);
t_point			_position(t_ray ray, float t);
t_sphere		_sphere(t_point o, float radius);
t_quadratic		discriminant(t_ray ray, t_sphere sp);
t_intersection	intersect(t_ray ray, t_sphere sp);

#endif
