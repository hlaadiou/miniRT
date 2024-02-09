/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:38:27 by azgaoua           #+#    #+#             */
/*   Updated: 2024/02/09 15:54:07 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include <libc.h>
#include "libft/libft.h"

typedef struct s_A
{
	int ambient_l_r;
	int RGB[3];
}		t_A;

typedef struct s_C
{
	int coor[3];
	int nor_o_v[3];
	int fov;
}		t_C;

typedef struct s_L
{
	int coor[3];
	int bright;
	// int *RGB;
}		t_L;

typedef struct s_sp
{
	int coor[3];
	int diameter;
	int RGB[3];
}		t_sp;

typedef struct s_pl
{
	int coor[3];
	int nor_n_v[3];
	int RGB[3];
}		t_pl;

typedef struct s_cy
{
	int coor[3];
	int nor_n_v[3];
	int diameter;
	int height;
	int RGB[3];
}		t_cy;

typedef struct s_rt
{
	t_A	*A;
	t_C	*C;
	t_L	*L;
	t_sp	*sp;
	t_pl	*pl;
	t_cy	*cy;
}				t_rt;

int open_tests(char **av);
void	ambient_lightning(char *line,t_rt **rt);






#endif