/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_mathematics.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:36:31 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/02/17 13:44:23 by azgaoua          ###   ########.fr       */
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

typedef struct s_matrix
{
	float	**mtx;
	int		size;
}	t_matrix;
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

float 		cofactor(t_matrix *a, int r, int c);
float		minor(t_matrix *a, int r, int c);
float		mtx_determinant(t_matrix *a);
t_matrix	*identity_mtx(int size);
t_matrix	*mtx_create(int size);
t_matrix	*mtx_multiply(t_matrix *a,t_matrix *b);
t_matrix	*submatrix(t_matrix *a, int r, int c);
t_matrix 	*mtx_transpose(t_matrix  *a);
t_matrix	*inverse(t_matrix *a);

#endif
