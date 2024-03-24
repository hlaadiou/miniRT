/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 19:59:11 by azgaoua           #+#    #+#             */
/*   Updated: 2024/03/24 22:09:24 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARS_H
# define PARS_H

# include "../libft/libft.h"
# include <limits.h>

typedef struct s_pars
{
	char					*identifier;
	char					**elements;
	int						flag;
	struct s_pars			*next;
}				t_pars;

typedef struct s_float
{
	float	whole;
	float	decimal;
	float	sign;
}	t_float;

typedef struct s_tuple
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_tuple;

typedef t_tuple t_point;
typedef t_tuple t_vector;

typedef struct s_rgb255
{
	int	r;
	int	g;
	int	b;
}	t_rgb255;

typedef struct s_ambient
{
	float		scale;
	t_rgb255	color;
}	t_ambient;

typedef struct s_camera
{
	t_point		view_point;
	t_vector	orientation;
	float		fov;
}	t_camera;

typedef struct s_light
{
	t_point		light_point;
	float		scale;
	t_rgb255	color;
}	t_light;

typedef struct s_scene
{
	t_ambient	*ambient;
	t_camera	*camera;
	t_light		*light;
}	t_scene;

// AZGAOUA
char		**str_split(char *str, char *seps);
int			ft_tab_size(char	**tab);
void		ft_ambient(char	*line, t_pars **pars);
void		ft_camera(char *line, t_pars **pars);
void		ft_light(char *line, t_pars **pars);
void		ft_lstadd_back(t_pars **lst, t_pars *n);
void		ft_pars_spher(char *line, t_pars **pars);
t_pars		*ft_lstnew(char *content, char **elms, int flag);
void		plane_pars(char *line, t_pars **pars);
void		cylinder_pars(char *line, t_pars **pars);
void		free_tab(char	**tab);
int			ft_lstsize(t_pars *lst);

//HLAADIOU
int 		check_al(t_pars *conf);
int 		check_camera(t_pars *conf);
int 		check_light(t_pars *conf);
int 		check_objects(t_pars *conf);
int 		check_required_elements(t_pars *conf);

float		ft_atof(char *str);
int			valid_float(char *str);
int			isnumber(char **str);
int			is_int(char **str);

t_tuple 	*parse_coordinates(char *str);
t_rgb255	*parse_color(char *str);

#endif
