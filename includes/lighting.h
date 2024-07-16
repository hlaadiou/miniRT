/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:42:22 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/07/16 11:40:02 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_H
# define LIGHTING_H

# include "miniRT.h"


typedef struct s_rgb255 t_rgb255;
typedef struct s_world t_world;
typedef struct s_scene t_scene;
typedef struct s_comps t_comps;

/* 0 <= r,g,b <= 1 */
typedef struct s_color
{
	float	r;
	float	g;
	float	b;
}	t_color;

typedef struct s_light
{
	t_point		position;
	float		brightness;
	t_color		color;
}	t_light;

typedef struct s_specs t_specs;

typedef struct s_phong
{
	t_vector	n;
	t_vector	l;
	t_vector	r;
	t_vector	e;
	t_color		px_color;
	t_color		ambient;
	t_color		diffuse;
	t_color		specular;
}	t_phong;

t_specs		_specs(float r, float g, float b, float ph);
t_light		_light(t_point pos, float br, t_color c);
t_color		_color(float r, float g, float b);
t_color		_color01(t_rgb255 c);
t_color		_color255(t_color c);
t_phong		_phong(t_object *obj, t_point px, t_light light, t_point cam);
t_color		illuminate(t_comps *comps,t_light light, int in_shadow);
t_color		schur_product(t_color col1, t_color col2);
t_color		multiply_color_scalar(float scalar, t_color tup);
int			is_shadowed(t_scene *w, t_point p);


#endif
