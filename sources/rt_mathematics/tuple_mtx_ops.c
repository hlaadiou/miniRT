/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_mtx_ops.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:51:56 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/07/31 20:10:28 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_tuple	extract_tuple_mtx(int row, t_matrix *m)
{
	t_tuple	tup;

	if (!m)
		put_error("Null matrix pointer\n");
	tup.x = m->mtx[row][0];
	tup.y = m->mtx[row][1];
	tup.z = m->mtx[row][2];
	tup.w = m->mtx[row][3];
	return (tup);
}

t_tuple	mtx_tuple_prod(t_matrix *mtx, t_tuple tup)
{
	t_tuple	prod;

	if (!mtx)
		put_error("Null matrix pointer\n");
	prod.x = dot_product(extract_tuple_mtx(0, mtx), tup);
	prod.y = dot_product(extract_tuple_mtx(1, mtx), tup);
	prod.z = dot_product(extract_tuple_mtx(2, mtx), tup);
	prod.w = dot_product(extract_tuple_mtx(3, mtx), tup);
	return (prod);
}
