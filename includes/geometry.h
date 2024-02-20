/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:58:11 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/02/20 17:28:53 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRY_H
# define GEOMETRY_H

# include "rt_mathematics.h"

typedef enum e_types
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_types;

/*
 * USER DEFINED DATA TYPES
 */

typedef struct s_ray
{
	t_point		org;
	t_vector	dir;
}	t_ray;

typedef struct s_roots
{
	float	t1;
	float	t2;
	int		counter;
}	t_roots;

typedef struct s_quadratic
{
	float	a;
	float	b;
	float	c;
	float	delta;
}	t_quadratic;

typedef struct s_sphere t_sphere;
typedef struct s_object	t_object;

typedef struct s_inter
{
	float		t;
	t_object	*obj;
}	t_inter;

typedef struct s_lst_inter
{
	t_inter					*inter;
	struct s_lst_inter		*prev;
	struct s_lst_inter		*next;
}	t_lst_inter;

/*
 * GEOMETRIC SHAPES
 */

typedef struct s_sphere
{
	t_point		org;
	float		radius;
	t_types		type;
}	t_sphere;

typedef struct s_cylinder
{
	t_types	type;
}	t_cylinder;

typedef struct s_plane
{
	t_types	type;
}	t_plane;

typedef struct s_object
{
	t_types		type;
	t_sphere	*sp;
	t_cylinder	*cy;
	t_plane		*pl;
}	t_object;

/*
 * FUNCTIONS PROTOTYPES
 */

t_ray			*_ray(t_point org, t_vector vec);
t_point			_position(t_ray *ray, float t);
t_sphere		*_sphere(t_point o, float radius);
t_quadratic		discriminant(t_ray *ray, t_sphere *sp);
t_inter			**intersect(t_ray *ray, t_sphere *sp);
int				_intersections(t_lst_inter **lst, t_inter **i);
t_lst_inter		*lst_last(t_lst_inter *inters);

#endif
