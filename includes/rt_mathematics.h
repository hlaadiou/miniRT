/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_mathematics.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:36:31 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/02/16 17:21:58 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MATHEMATICS_H
# define RT_MATHEMATICS_H

# include <math.h>

/*
 * STRUCTURES
 */

typedef struct s_matrix
{
	float	**mtx;
	int		size;
}	t_matrix;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

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
