/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:58:11 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/03/30 17:54:03 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRY_H
# define GEOMETRY_H

# include "rt_mathematics.h"

typedef struct s_rgb255 t_rgb255;

typedef enum e_types
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_types;

/*
 * USER DEFINED DATA TYPES *
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

typedef struct s_sphere	t_sphere;
typedef struct s_object	t_object;
typedef struct s_color	t_color;

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
 * GEOMETRIC SHAPES *
 */

typedef struct s_sphere
{
	t_point		org;
	float		radius;
	t_types		type;
}	t_sphere;

typedef struct s_cylinder
{
	t_point		center;
	t_vector	axis;
	float		diameter;
	float		height;
	t_types		type;
}	t_cylinder;

typedef struct s_plane
{
	t_point		pt;
	t_vector	vec;
	t_types		type;
}	t_plane;

typedef struct s_specs
{
	float	ambient;
	float	diffuse;
	float	specular;
	float	phong_factor;
}	t_specs;

/* GENERIC TYPE FOR (CY/SP/PL..) */
typedef struct s_object
{
	t_types		type;
	t_sphere	*sp;
	t_cylinder	*cy;
	t_plane		*pl;
	t_matrix	*transform;
	t_specs		specs;
	t_rgb255	*color;
}	t_object;

typedef struct s_comps
{
	float 		t;
	t_object	*obj;
	t_point		point;
	t_vector    normalv;
	t_vector    eyev;
	t_tuple		over_point;
	int 		inside;

}	t_comps;

/*
 * FUNCTIONS PROTOTYPES *
 */

t_ray			*_ray(t_point org, t_vector vec);
t_point			_position(t_ray *ray, float t);
t_object		*_sphere(t_point o, float radius, t_rgb255 *c);
t_object    	*_plane(t_point pt, t_vector vec, t_rgb255 *c);
t_object    	*_cylinder(t_point pt, t_vector axis, float d, float h, t_rgb255 *c);
t_quadratic		discriminant_sp(t_ray *ray, t_object *sp);
t_inter			**intersect_sp(t_ray *ray, t_object *sp);
t_object		*_obj(void *obj, t_rgb255 *color, t_types type);
int				_intersections(t_lst_inter **lst, t_inter **i);
t_inter 		**_intersection(t_roots roots, t_object *obj);
t_lst_inter		*lst_last(t_lst_inter *inters);
t_inter			*hit(t_lst_inter *lst);
t_ray			*transform(t_ray *ray, t_matrix *a);
t_vector		vec_normalize(t_vector vec);
void			set_transform(t_object **obj, t_matrix *mtx);
t_vector 		normal_at(t_object *sp, t_point pnt);


#endif
