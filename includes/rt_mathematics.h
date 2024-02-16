/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_mathematics.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:36:31 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/02/16 14:43:43 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MATHEMATICS_H
# define RT_MATHEMATICS_H

# include <math.h>

/*
 * STRUCTURES
 */

typedef struct s_matrix
{
	float	**mtx;
	int		size;
}	t_matrix;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

#endif
