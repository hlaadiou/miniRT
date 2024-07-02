/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_mtx_ops.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:51:56 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/07/02 17:45:09 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_tuple	extract_tuple_mtx(int row, t_matrix *m)
{
	t_tuple	tup;
    
    if (!m) {
        fprintf(stderr, "Error: Null matrix pointer\n");
        return (t_tuple){0, 0, 0, 0};
    }
	tup.x = m->mtx[row][0];
	tup.y = m->mtx[row][1];
	tup.z = m->mtx[row][2];
	tup.w = m->mtx[row][3];
	return (tup);
}

t_tuple mtx_tuple_prod(t_matrix *mtx, t_tuple tup) {
    t_tuple prod;

    // Ensure mtx and tup are valid
    if (!mtx) {
        fprintf(stderr, "Error: Null matrix pointer\n");
        return (t_tuple){0, 0, 0, 0};
    }
    prod.x = dot_product(extract_tuple_mtx(0, mtx), tup);
    prod.y = dot_product(extract_tuple_mtx(1, mtx), tup);
    prod.z = dot_product(extract_tuple_mtx(2, mtx), tup);
    prod.w = dot_product(extract_tuple_mtx(3, mtx), tup);

    return prod;
}
