/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:03:36 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/03/26 07:23:26 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_object	*_plane(t_point pt, t_vector vec, t_rgb255 *c)
{
	t_plane	*pl;

	pl = (t_plane *)malloc(sizeof(t_plane));
	if (!pl)
		return (NULL);
	*pl = (t_plane){pt, vec, PLANE}; 
	return (_obj(pl, c, PLANE));
}
