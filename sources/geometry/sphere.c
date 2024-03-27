/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:03:38 by hlaadiou          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/02 18:55:40 by azgaoua          ###   ########.fr       */
=======
/*   Updated: 2024/03/26 06:19:09 by hlaadiou         ###   ########.fr       */
>>>>>>> baabf1ba5d9dd357c0eac69cf2034f2ffddb18a6
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

<<<<<<< HEAD
t_object	*_sphere(t_point o, float radius, t_color c)
=======
t_object	*_sphere(t_point o, float radius, t_rgb255 *c)
>>>>>>> baabf1ba5d9dd357c0eac69cf2034f2ffddb18a6
{
	t_sphere	*sp;

	sp = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sp)
		return (NULL);
	*sp = (t_sphere){o, radius, SPHERE}; 
<<<<<<< HEAD
	return (_obj(sp, SPHERE, c));
=======
	return (_obj(sp, c, SPHERE));
>>>>>>> baabf1ba5d9dd357c0eac69cf2034f2ffddb18a6
}
