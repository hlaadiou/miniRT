/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:32:21 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/02/20 18:18:40 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_mathematics.h"

int	compare_tuples(t_tuple tup1, t_tuple tup2)
{
	if (compare_f(tup1.x, tup2.x) && compare_f(tup1.y, tup2.y) \
			&& compare_f(tup1.z, tup2.z) && compare_f(tup1.w, tup2.w))
		return (1);
	return (0);
}

t_tuple	add_tuples(t_tuple tup1, t_tuple tup2)
{
	t_tuple	sum;

	sum.x = tup1.x + tup2.x;
	sum.y = tup1.y + tup2.y;
	sum.z = tup1.z + tup2.z;
	sum.w = tup1.w + tup2.w;
	return (sum);
}

t_tuple	subtract_tuples(t_tuple tup1, t_tuple tup2)
{
	t_tuple	diff;

	diff.x = tup1.x - tup2.x;
	diff.y = tup1.y - tup2.y;
	diff.z = tup1.z - tup2.z;
	diff.w = tup1.w - tup2.w;
	return (diff);
}

t_tuple	multiply_tuple_scalar(float scalar, t_tuple tup)
{
	t_tuple	res;

	res.x = scalar * tup.x;
	res.y = scalar * tup.y;
	res.z = scalar * tup.z;
	res.w = scalar * tup.w;
	return (res);
}
