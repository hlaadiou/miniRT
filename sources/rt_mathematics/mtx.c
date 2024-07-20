/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:24:48 by azgaoua           #+#    #+#             */
/*   Updated: 2024/07/19 04:41:01 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_matrix	*_mtx(int size)
{
	t_matrix	*mtx;
	int			i;

	mtx = (t_matrix *)ft_malloc(sizeof(t_matrix));
	mtx->size = size;
	mtx->mtx = (float **)ft_malloc(sizeof(float *) * size);
	i = -1;
	while (++i < size)
		mtx->mtx[i] = (float *)ft_malloc(sizeof(float) * size);
	return (mtx);
}

t_matrix	*submatrix(t_matrix *a, int r, int c)
{
	t_matrix	*sub;
	int			i;
	int			j;
	int			row;
	int			col;

	sub = _mtx(a->size - 1);
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

t_matrix	*_identity(int size)
{
	t_matrix	*a;
	int			i;
	int			j;

	i = 0;
	a = _mtx(size);
	while (i < size)
	{
		j = 0;
		while (j < size)
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

t_matrix	*mtx_multiply(t_matrix *a, t_matrix *b)
{
	t_matrix	*c;
	int			i;
	int			j;
	int			k;

	c = _mtx(a->size);
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
