/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:24:48 by azgaoua           #+#    #+#             */
/*   Updated: 2024/02/16 13:11:56 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_mathematics.h"
#include <stdlib.h>
#include <stdio.h>

float	**mtx_multiply(float A[4][4], float B[4][4])
{
	float	**C;
	int		i;
	int		j;
	int		k;

	C = (float **)malloc(8 * 4);
	i = -1;
	while (++i < 4)
		C[i] = (float *)malloc(4 * 4);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			C[i][j] = 0;
			k = -1;
			while (++k < 4)
				C[i][j] += A[i][k] * B[k][j];
		}
	}
	return (C);
}


float **mtx_transpose(float  A[4][4])
{
	float **C;
	int	k;
	int	r;
	int	c;

	r = -1;
	C = (float **)malloc(32);
	k = -1;
	while (++k < 4)
		C[k] = (float *)malloc(16);
	while (++r < 4)
	{
		c = -1;
		while (++c < 4)
			C[c][r] = A[r][c];
	}
	return (C);
}

int main()
{
	float	A[4][4];
	float	B[4][4];
	
	A[0][0] = 1;
	A[0][1] = 2;
	A[0][2] = 3;
	A[0][3] = 4;
	A[1][0] = 5;
	A[1][1] = 6;
	A[1][2] = 7;
	A[1][3] = 8;
	A[2][0] = 9;
	A[2][1] = 8;
	A[2][2] = 7;
	A[2][3] = 6;
	A[3][0] = 5;
	A[3][1] = 4;
	A[3][2] = 3;
	A[3][3] = 2;
	B[0][0] = -2;
	B[0][1] = 1;
	B[0][2] = 2;
	B[0][3] = 3;
	B[1][0] = 3;
	B[1][1] = 2;
	B[1][2] = 1;
	B[1][3] = -1;
	B[2][0] = 4;
	B[2][1] = 3;
	B[2][2] = 6;
	B[2][3] = 5;
	B[3][0] = 1;
	B[3][1] = 2;
	B[3][2] = 7;
	B[3][3] = 8;
	// printf("**************************************************\n");
	// float **C = mtx_multiply(A, B);
	// for (int i = 0; i < 4; i++)
	// {
	// 	printf(" |");
	// 	for (int j = 0; j < 4; j++)
	// 		printf("%.2f |", C[i][j]);
	// 	printf("\n");
	// }
	printf("**************************************************\n");
	float **C = mtx_transpose(A);
	for (int i = 0; i < 4; i++)
	{
		printf(" |");
		for (int j = 0; j < 4; j++)
			printf("%.2f |", C[i][j]);
		printf("\n");
	}
	return 0;
}