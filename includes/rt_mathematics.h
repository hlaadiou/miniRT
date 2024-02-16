/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_mathematics.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:36:31 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/02/16 18:48:14 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MATHEMATICS_H
# define RT_MATHEMATICS_H

# define EPSILON 0.0001

# include <math.h>
# include <stdio.h>
# include <stdlib.h>

/*
 * STRUCTURES
 */

typedef struct s_tuple
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_tuple;

typedef t_tuple t_point;
typedef t_tuple t_vector;

/* FUNCTIONS PROTOTYPES */

int			compare_f(float a, float b);
t_point		_point(float x, float y, float z);
t_vector	_vector(float x, float y, float z);

#endif
