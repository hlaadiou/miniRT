/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 04:41:16 by azgaoua           #+#    #+#             */
/*   Updated: 2024/07/19 04:42:37 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_matrix	*inverse(t_matrix *a)
{
	t_matrix	*b;
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
	t_matrix	*sub;
	float		minor_value;

	sub = submatrix(a, r, c);
	minor_value = mtx_determinant(sub);
	return (minor_value);
}

float	cofactor(t_matrix *a, int r, int c)
{
	if ((r + c) % 2 == 0)
		return (minor(a, r, c));
	return (minor(a, r, c) * -1);
}

t_matrix	*mtx_transpose(t_matrix *a)
{
	t_matrix	*c;
	int			r;
	int			col;

	r = -1;
	c = _mtx(a->size);
	while (++r < a->size)
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
	int	row;
	int	col;

	row = 0;
	if (a->size != b->size)
		return (0);
	while (row < a->size)
	{
		col = 0;
		while (col < a->size)
		{
			if (compare_f(a->mtx[row][col], b->mtx[row][col]) == 0)
				return (0);
			col++;
		}
		row++;
	}
	return (1);
}
