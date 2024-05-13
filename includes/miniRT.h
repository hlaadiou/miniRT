/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:15:01 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/05/02 17:27:48 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "rt_mathematics.h"
# include "geometry.h"
# include "lighting.h"
# include "pars.h"


typedef struct		s_rt
{
	/*----------- to do 
	
    *

	to do -----------*/
}					t_rt;

t_ray *transform_ray(t_ray *ray, t_matrix *a);


#endif
