/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:53:36 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/03/01 16:06:54 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/* 0 <= r,g,b <= 1 */
t_color	_color(float r, float g, float b)
{
	t_color	c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

/* 0 <= r,g,b <= 255 */
t_color	_color255(float r, float g, float b)
{
	t_color	c;

	c.r = r * 255;
	c.g = g * 255;
	c.b = b * 255;
	return (c);
}