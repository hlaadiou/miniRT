/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:41:07 by azgaoua           #+#    #+#             */
/*   Updated: 2024/07/20 17:21:18 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_vector	reflect(t_vector a, t_vector n)
{
	return (subtract_tuples(a, \
			multiply_tuple_scalar((2 * dot_product(a, n)), n)));
}
