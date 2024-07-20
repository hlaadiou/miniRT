/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:44:03 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/07/20 17:21:13 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/* GENERATES A TUPLE WITH A W-COMPONENT OF VALUE 1 */
t_point	_point(float x, float y, float z)
{
	t_point	pt;

	pt.x = x;
	pt.y = y;
	pt.z = z;
	pt.w = 1;
	return (pt);
}
