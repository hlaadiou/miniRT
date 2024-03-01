/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:53:36 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/03/01 10:59:25 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/* 0 <= r,g,b <= 1 */
t_color	_color(float r, float g, float b)
{
	t_color	c;

	c.r = (int) r * 255;
	c.g = (int) g * 255;
	c.b = (int) b * 255;
	return (c);
}
