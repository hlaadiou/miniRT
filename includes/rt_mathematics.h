/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_mathematics.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:36:31 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/07/16 02:00:01 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MATHEMATICS_H
# define RT_MATHEMATICS_H

# define EPSILON 0.001

/*
 * USER DEFINED DATA TYPES
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

typedef struct s_object t_object;

/* FUNCTIONS PROTOTYPES */

int			compare_f(float a, float b);
t_point		_point(float x, float y, float z);
t_vector	_vector(float x, float y, float z);

int			mtx_compare(t_matrix *a, t_matrix *b);
float 		cofactor(t_matrix *a, int r, int c);
float		minor(t_matrix *a, int r, int c);
float		mtx_determinant(t_matrix *a);
t_matrix	*_identity(int size);
t_matrix	*_mtx(int size);
t_matrix	*mtx_multiply(t_matrix *a,t_matrix *b);
t_matrix	*submatrix(t_matrix *a, int r, int c);
t_matrix 	*mtx_transpose(t_matrix  *a);
t_matrix	*inverse(t_matrix *a);
t_matrix	*rotation_x(float r);
t_matrix	*rotation_y(float r);
t_matrix	*rotation_z(float r);
t_matrix	*shearing(float x_y, float x_z, float y_x, \
						float y_z, float z_x, float z_y);
t_matrix 	*translation(float x, float y, float z);
t_matrix	*scaling_mtx(float x, float y, float z);
				

float		dot_product(t_vector vec1, t_vector vec2);
t_tuple		extract_tuple_mtx(int row, t_matrix *m);
t_tuple 	mtx_tuple_prod(t_matrix *mtx, t_tuple tup);


int			compare_tuples(t_tuple tup1, t_tuple tup2);
t_tuple		add_tuples(t_tuple tup1, t_tuple tup2);
t_tuple		subtract_tuples(t_tuple tup1, t_tuple tup2);
t_tuple		multiply_tuple_scalar(float scalar, t_tuple tup);

t_vector 	normal_at(t_object *sp, t_point pnt);
t_vector	reflect(t_vector a, t_vector n);
t_matrix 	*cylinder_axis_to_matrix(double ex, double ey, double ez, t_matrix *matrix);

#endif
