/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:24:48 by azgaoua           #+#    #+#             */
/*   Updated: 2024/07/18 10:35:04 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// No Protection ?
t_matrix	*_mtx(int size)
{
	t_matrix	*mtx;
	int			i;

	mtx = (t_matrix	*)malloc(sizeof(t_matrix));
	if (!mtx)
	{
		put_error("Fatal: Cannot allocate enough memory\n");
		return (NULL);
	}
	mtx->size = size;
	mtx->mtx = (float **)malloc(sizeof(float *) * size);
	if (!(mtx->mtx))
	{
		put_error("Fatal: Cannot allocate enough memory\n");
		return (NULL);
	}
	i = -1;
	while (++i < size)
	{
		mtx->mtx[i] = (float *)malloc(sizeof(float) * size);
		if (!(mtx->mtx[i]))
		{
			put_error("Fatal: Cannot allocate enough memory\n");
			return (NULL);
		}
	}
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

t_matrix	*inverse(t_matrix *a)
{
	t_matrix	*b = NULL;
	int			row;
	int			col;
	float		c;
	
	if (mtx_determinant(a) == 0)
		return (NULL);
	row = 0;
	b = _mtx(a->size);
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
	c = _mtx(a->size);
	while (++r < 4)
	{
		col = -1;
		while (++col < c->size)
			c->mtx[col][r] = a->mtx[r][col];
	}
	return (c);
}

/*  return 1 if the (mtx_a) and (mtx_b) are the same and 0 other ways */
int	mtx_compare(t_matrix *a, t_matrix *b)
{
	int row;
	int col;
	
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

