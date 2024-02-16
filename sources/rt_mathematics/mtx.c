/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:24:48 by azgaoua           #+#    #+#             */
/*   Updated: 2024/02/16 15:26:01 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_mathematics.h"
#include <stdlib.h>
#include <stdio.h>

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

float	mtx_determinant(t_matrix a)
{
	float	dtr;

	dtr = 0;
	return (dtr);
}

t_matrix *mtx_transpose(t_matrix  *a)
{
	t_matrix *c;
	int	k;
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

int main()
{
	t_matrix *A;
	t_matrix *B;

	A = mtx_create(4);
	B = mtx_create(4);
	A->mtx[0][0] = 1;
	A->mtx[0][1] = 2;
	A->mtx[0][2] = 3;
	A->mtx[0][3] = 4;
	A->mtx[1][0] = 5;
	A->mtx[1][1] = 6;
	A->mtx[1][2] = 7;
	A->mtx[1][3] = 8;
	A->mtx[2][0] = 9;
	A->mtx[2][1] = 8;
	A->mtx[2][2] = 7;
	A->mtx[2][3] = 6;
	A->mtx[3][0] = 5;
	A->mtx[3][1] = 4;
	A->mtx[3][2] = 3;
	A->mtx[3][3] = 2;
	B->mtx[0][0] = -2;
	B->mtx[0][1] = 1;
	B->mtx[0][2] = 2;
	B->mtx[0][3] = 3;
	B->mtx[1][0] = 3;
	B->mtx[1][1] = 2;
	B->mtx[1][2] = 1;
	B->mtx[1][3] = -1;
	B->mtx[2][0] = 4;
	B->mtx[2][1] = 3;
	B->mtx[2][2] = 6;
	B->mtx[2][3] = 5;
	B->mtx[3][0] = 1;
	B->mtx[3][1] = 2;
	B->mtx[3][2] = 7;
	B->mtx[3][3] = 8;
	printf("**************************************************\n");
	t_matrix *c = mtx_multiply(A, B);
	for (int i = 0; i < c->size; i++)
	{
		printf(" |");
		for (int j = 0; j < c->size; j++)
			printf("%.2f |", c->mtx[i][j]);
		printf("\n");
	}
	printf("**************************************************\n");
	t_matrix *a = identity_mtx(4);
	for (int i = 0; i < a->size; i++)
	{
		printf(" |");
		for (int j = 0; j < a->size; j++)
			printf("%.2f |", a->mtx[i][j]);
		printf("\n");
	}
	// printf("**************************************************\n");
	// t_matrix *C = mtx_transpose(A);
	// for (int i = 0; i < 4; i++)
	// {
	// 	printf(" |");
	// 	for (int j = 0; j < C->size; j++)
	// 		printf("%.2f |", C->mtx[i][j]);
	// 	printf("\n");
	// }
	return 0;
}