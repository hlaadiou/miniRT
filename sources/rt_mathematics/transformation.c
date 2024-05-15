/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:11:31 by azgaoua           #+#    #+#             */
/*   Updated: 2024/05/15 16:58:22 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	set_transform(t_object **obj, t_matrix *mtx)
{
	(*obj)->transform = mtx_multiply(mtx, (*obj)->transform);
}

t_ray	*transform(t_ray *ray, t_matrix *a)
{
	t_ray *b;

	b = _ray(ray->org, ray->dir);
	b->org =  mtx_tuple_prod(a, ray->org);
	b->dir =  mtx_tuple_prod(a, ray->dir);
	return (b);
}

