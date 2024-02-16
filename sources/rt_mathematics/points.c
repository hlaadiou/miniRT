/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:44:03 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/02/16 18:48:20 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt_mathematics.h"

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
