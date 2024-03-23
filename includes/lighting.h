/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:42:22 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/03/03 17:04:03 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_H
# define LIGHTING_H

# include "geometry.h"
# include "rt_mathematics.h"

/* 0 <= r,g,b <= 1 */
typedef struct s_color
{
	float	r;
	float	g;
	float	b;
}	t_color;

typedef struct s_light
{
	t_point	position;
	float	brightness;
	t_color	color;
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
t_phong		_phong(t_object *obj, t_point px, t_light light, t_point cam);
t_color		illuminate(t_object *obj, t_point px, t_light light, t_point cam);
t_color		schur_product(t_color col1, t_color col2);
t_color		_color255(t_color c);
t_color		multiply_color_scalar(float scalar, t_color tup);


#endif
