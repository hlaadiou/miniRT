/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:53:36 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/03/31 10:35:40 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_color	_color01(t_rgb255 c)
{
	t_color	color;

	color.r = c.r / 255;
	color.g = c.g / 255;
	color.b = c.b / 255;
	return (color);
}

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
t_color	_color255(t_color c)
{
	t_color	color;

	color.r = c.r * 255;
	color.g = c.g * 255;
	color.b = c.b * 255;
	return (color);
}
