/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:03:36 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/03/30 23:14:02 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_object	*_plane(t_point pt, t_vector vec, t_color c)
{
	t_plane	*pl;

	pl = (t_plane *)malloc(sizeof(t_plane));
	if (!pl)
		return (NULL);
	*pl = (t_plane){pt, vec, PLANE}; 
	return (_obj(pl, c, PLANE));
}
