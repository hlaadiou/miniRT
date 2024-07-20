/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:03:38 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/07/20 16:39:15 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_object	*_sphere(t_point o, float radius, t_color c)
{
	t_sphere	*sp;

	sp = (t_sphere *)ft_malloc(sizeof(t_sphere));
	if (!sp)
		return (NULL);
	*sp = (t_sphere){o, radius, SPHERE};
	return (_obj(sp, c, SPHERE));
}
