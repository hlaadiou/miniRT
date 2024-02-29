/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:42:22 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/02/29 19:43:59 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_H
# define LIGHTING_H

# include "geometry.h"

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
}	t_phong;

t_specs		_specs(float r, float g, float b, float ph);
t_light		_light(t_point pos, float br, t_color c);
t_color		_color(float r, float g, float b);

#endif
