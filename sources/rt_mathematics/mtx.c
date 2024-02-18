/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:24:48 by azgaoua           #+#    #+#             */
/*   Updated: 2024/02/18 15:36:11 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_mathematics.h"

t_matrix	*mtx_create(int size)
{
	t_matrix	*mtx;
	int			i;

	mtx = (t_matrix	*)malloc(sizeof(t_matrix));
	mtx->size = size;
	mtx->mtx= (float **)malloc(sizeof(float *) * size);
	i = -1;
	while (++i < size)
		mtx->mtx[i] = (float *)malloc(sizeof(float) * size);
	return (mtx);
}

t_matrix	*submatrix(t_matrix *a, int r, int c)
{
	t_matrix	*sub;
	int			i;
	int			j;
	int			row;
	int			col;

	sub = mtx_create(a->size - 1);
	i = -1;
	row = 0;
	while (++i < a->size)
	{
		if (i == r)
			continue ;
		j = -1;
		col = 0;
		while (++j < a->size)
		{
			if (j == c)
				continue ;
			sub->mtx[row][col] = a->mtx[i][j];
			col++;
		}
		row++;
	}
	return (sub);
}


t_matrix	*identity_mtx(int size)
{
	t_matrix	*a;
	int			i;
	int			j;

	i = 0;
	a = mtx_create(size);
	while(i < size)
	{
		j = 0;
		while(j < size)
		{
			if (i == j)
				a->mtx[i][j] = 1;
			else
				a->mtx[i][j] = 0;
			j++;
		}
		i++;
	}
	return (a);
}

t_matrix	*mtx_multiply(t_matrix *a,t_matrix *b)
{
	t_matrix	*c;
	int			i;
	int			j;
	int			k;

	c = mtx_create(a->size);
	i = -1;
	while (++i < a->size)
	{
		j = -1;
		while (++j < a->size)
		{
			c->mtx[i][j] = 0;
			k = -1;
			while (++k < a->size)
				c->mtx[i][j] += a->mtx[i][k] * b->mtx[k][j];
		}
	}
	return (c);
}

float	mtx_determinant(t_matrix *a)
{
	float	dtr;
	int		i;

	i = 0;
	dtr = 0;
	if (a->size == 2)
		dtr = (a->mtx[0][0] * a->mtx[1][1]) - (a->mtx[0][1] * a->mtx[1][0]);
	else
	{
		while (i < a->size)
		{
			dtr += a->mtx[0][i] * cofactor(a, 0, i);
			i++;
		}
	}
	return (dtr);
}

t_matrix	*inverse(t_matrix *a)
{
	t_matrix	*b;
	int			row;
	int			col;
	float		c;
	
	if (mtx_determinant(a) == 0)
		return (NULL);
	row = 0;
	b = mtx_create(a->size);
	while (row < a->size)
	{
		col = 0;
		while (col < a->size)
		{
			c = cofactor(a, row, col);
			b->mtx[col][row] = c / mtx_determinant(a);
			col++;
		}
		row++;
	}
	return (b);
}

float	minor(t_matrix *a, int r, int c)
{
	return (mtx_determinant(submatrix(a, r, c)));
}

float cofactor(t_matrix *a, int r, int c)
{
	return (((r + c) % 2 == 0) ? minor(a, r, c) : (minor(a, r, c) * -1));
}

t_matrix *mtx_transpose(t_matrix  *a)
{
	t_matrix *c;
	int	r;
	int	col;

	r = -1;
	c = mtx_create(a->size);
	while (++r < 4)
	{
		col = -1;
		while (++col < c->size)
			c->mtx[col][r] = a->mtx[r][col];
	}
	return (c);
}

int	mtx_compare(t_matrix *a, t_matrix *b)
{
	unsigned int row;
	unsigned int col;
	
	row = 0;
	if (a->size != b->size)
		return (0);
	while (row < a->size)
	{
		col = 0;
		while (col < a->size)
		{
			if (compare_f(a->mtx[row][col],b->mtx[row][col]) == 0)
				return (0);
			col++;
		}
		row++;
	}
	return (1);
}

// int main()
// {
// 	t_matrix *A;
// 	t_matrix *B;

// 	A = mtx_create(4);
// 	B = mtx_create(4);
// 	/*
// 	| 9 | 3 | 0 | 9 |
// 	| -5 | -2 | -6 | -3 |
// 	| -4 | 9 | 6 | 4 |
// 	| -7 | 6 | 6 | 2 |
// 	*/
// 	A->mtx[0][0] = 1;
// 	A->mtx[0][1] = 2;
// 	A->mtx[0][2] = 3;
// 	A->mtx[0][3] = 4;
// 	A->mtx[1][0] = 2;
// 	A->mtx[1][1] = 4;
// 	A->mtx[1][2] = 4;
// 	A->mtx[1][3] = 2;
// 	A->mtx[2][0] = 8;
// 	A->mtx[2][1] = 6;
// 	A->mtx[2][2] = 4;
// 	A->mtx[2][3] = 1;
// 	A->mtx[3][0] = 0;
// 	A->mtx[3][1] = 0;
// 	A->mtx[3][2] = 0;
// 	A->mtx[3][3] = 1;
// 	B->mtx[0][0] = 2;
// 	B->mtx[0][1] = 1;
// 	B->mtx[0][2] = 2;
// 	B->mtx[0][3] = 3;
// 	B->mtx[1][0] = 3;
// 	B->mtx[1][1] = 2;
// 	B->mtx[1][2] = 1;
// 	B->mtx[1][3] = -1;
// 	B->mtx[2][0] = 4;
// 	B->mtx[2][1] = 3;
// 	B->mtx[2][2] = 6;
// 	B->mtx[2][3] = 5;
// 	B->mtx[3][0] = 1;
// 	B->mtx[3][1] = 2;
// 	B->mtx[3][2] = 7;
// 	B->mtx[3][3] = 8;

// 	t_matrix *transform_a = rotation_x(M_PI_2);
// 	t_matrix *transform_b = scaling_mtx(5, 5, 5);
// 	t_matrix *transform_c = translation(10, 5, 7);

// 	// transform = inverse(transform);
// 	t_point	tup = _point(1, 0, 1);
// 	t_tuple prod = mtx_tuple_prod(mtx_multiply(mtx_multiply(transform_c, transform_b), transform_a), tup);
// 	printf ("%.2f %.2f %.2f %.2f\n", prod.x, prod.y, prod.z, prod.w);
// 	printf("**************************************************\n");

// }
// 	// t_matrix *c = mtx_multiply(A, B);
// 	// for (int i = 0; i < c->size; i++)
// 	// {
// 	// 	printf(" |");
// 	// 	for (int j = 0; j < c->size; j++)
// 	// 		printf("%.2f |", c->mtx[i][j]);
// 	// 	printf("\n");
// 	// }
// 	// printf("**************************************************\n");
// 	// t_matrix *a = identity_mtx(4);
// 	for (int i = 0; i < B->size; i++)
// 	{
// 		printf(" |");
// 		for (int j = 0; j < B->size; j++)
// 			printf("%.5f |", B->mtx[i][j]);
// 		printf("\n");
// 	}
// 	printf("**************************************************\n");
// 	t_matrix *a = mtx_multiply(inverse(A) , B);
// 	a = mtx_multiply(A, a);
// 	for (int i = 0; i < a->size; i++)
// 	{
// 		printf(" |");
// 		for (int j = 0; j < a->size; j++)
// 			printf("%.5f |", a->mtx[i][j]);
// 		printf("\n");
// 	}
// 	// float f = minor(a, 0, 1);
// 	// printf("\n******%.2f*****\n", f);
// /*
// | 3 | 5 | 0 |
// | 2 | -1 | -7 |
// | 6 | -1 | 5 |
// */

// 	// printf("**************************************************\n");
// 	// t_matrix *C = mtx_create(3);
// 	// C->mtx[0][0] = 3;
// 	// C->mtx[0][1] = 5;
// 	// C->mtx[0][2] = 0;
// 	// C->mtx[1][0] = 2;
// 	// C->mtx[1][1] = -1;
// 	// C->mtx[1][2] = -7;
// 	// C->mtx[2][0] = 6;
// 	// C->mtx[2][1] = -1;
// 	// C->mtx[2][2] = 5;
// 	// for (int i = 0; i < C->size; i++)
// 	// {
// 	// 	printf(" |");
// 	// 	for (int j = 0; j < C->size; j++)
// 	// 		printf("%.2f |", C->mtx[i][j]);
// 	// 	printf("\n");
// 	// }
// 	// float f = minor(C, 0, 0);
// 	// printf("\nminor(C, 0, 0)******%.2f*****\n", f);
// 	// float f1 = cofactor(C, 0, 0);
// 	// printf("\ncofactor(C, 0, 0)******%.2f*****\n", f1);
// 	// float f2 = minor(C, 1, 0);
// 	// printf("\nminor(C, 1, 0)******%.2f*****\n", f2);
// 	// float f3 = cofactor(C, 1, 0);
// 	// printf("\ncofactor(C, 1, 0)******%.2f*****\n", f3);
// 	return 0;
// }
