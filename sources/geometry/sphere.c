/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:03:38 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/07/14 00:37:52 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_object	*_sphere(t_point o, float radius, t_color c)
{
	t_sphere	*sp;

	sp = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sp)
		return (NULL);
	*sp = (t_sphere){o, radius / 2.0f, SPHERE}; 
	return (_obj(sp, c, SPHERE));
}
