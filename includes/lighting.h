/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:42:22 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/03/27 08:22:01 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_H
# define LIGHTING_H

# include "miniRT.h"

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
	t_rgb255	*color;
}	t_light;

typedef struct s_specs t_specs;

typedef struct s_phong
{
	t_vector	n;
	t_vector	l;
	t_vector	r;
	t_vector	e;
	t_rgb255		*px_color;
	t_rgb255		*ambient;
	t_rgb255		*diffuse;
	t_rgb255		*specular;
}	t_phong;

t_specs		_specs(float r, float g, float b, float ph);
t_light		_light(t_point pos, float br, t_color c);
t_rgb255	*_color(float r, float g, float b);
t_phong		_phong(t_object *obj, t_point px, t_light light, t_point cam);
t_rgb255	*illuminate(t_object *obj, t_point px, t_light light, t_point cam);
t_rgb255	*schur_product(t_rgb255 *col1, t_rgb255 *col2);
t_color		_color255(t_color c);
t_rgb255	*multiply_color_scalar(float scalar, t_rgb255 *tup);


#endif
