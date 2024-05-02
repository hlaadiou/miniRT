/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 19:59:11 by azgaoua           #+#    #+#             */
/*   Updated: 2024/04/03 12:12:02 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARS_H
# define PARS_H

# define AMB     1
# define CAM     2
# define LIGHT   3
# define SP      4
# define PL      5
# define CY      6

# include "../lib/libft/libft.h"
# include "miniRT.h"
# include <limits.h>


typedef struct s_collector
{
	void				*ptr;
	struct s_collector	*next;
}	t_collector;

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

typedef struct s_rgb255
{
	int	r;
	int	g;
	int	b;
}	t_rgb255;

typedef struct s_ambient
{
	float		scale;
	t_color		color;
}	t_ambient;

typedef struct s_camera
{
	t_point		view_point;
	t_vector	orientation;
	float		fov;
}	t_camera;

// typedef struct s_light_src
// {
// 	t_point		position;
// 	float		brightness;
// 	t_color		color;
// }	t_light_src;

typedef t_light t_light_src;

typedef struct s_obj_lst
{
	t_object			*obj;
	struct s_obj_lst	*next;
	struct s_obj_lst	*prev;
}	t_obj_lst;

typedef struct		s_world
{
	t_light		light;
	t_obj_lst	*obj_lst;
}				t_world;


typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_obj_lst	*lst;
}	t_scene;

typedef struct s_camera_fn
{
	float		hsize;
	float       vsize;
	float		hwidth;
	float   	hheight;
	float		fov;
	float		pixel_size;
	t_matrix	*transform;
}	t_camera_fn;

// AZGAOUA
char			**str_split(char *str, char *seps);
int				ft_tab_size(char	**tab);
void			ft_ambient(char	*line, t_pars **pars);
void			ft_camera(char *line, t_pars **pars);
void			ft_light(char *line, t_pars **pars);
void			ft_lstadd_back(t_pars **lst, t_pars *new);
void			ft_pars_spher(char *line, t_pars **pars);
t_pars			*ft_lstnew(char *content, char **elms, int flag);
void			plane_pars(char *line, t_pars **pars);
void			cylinder_pars(char *line, t_pars **pars);
void			free_tab(char	**tab);
int				ft_lstsize(t_pars *lst);
void			ft_free_struct(t_pars *pars);
void			free_f_mtx(float **mtx, int size);
int 			check_cap(t_ray *r, float t);
t_vector		local_normal_at(t_object *cy, t_point world_point);

/* g_collector */

void			*ft_malloc(size_t size);
t_collector		**ft_collector(void);
t_collector		*ft_lstnew_clctr(void *lst);
void			ft_free_collector(t_collector **lst);
void			ft_lstadd_back_clctr(t_collector **lst, t_collector *new);
t_world			*init_world(t_scene *scene);
t_comps 		*prepare_computations(t_inter *inter, t_ray *ray);
t_color 		shade_hit(t_world *world, t_comps *copms);
t_color			color_at(t_world *w, t_ray *r);
void			render(t_camera_fn c, t_world *w, mlx_image_t **image);
t_inter 		**local_intersect(t_object *cy, t_ray *r);


//HLAADIOU
int 			check_al(t_pars *conf);
int 			check_camera(t_pars *conf);
int 			check_light(t_pars *conf);
int 			check_objects(t_pars *conf);
int 			check_required_elements(t_pars *conf);

float			ft_atof(char *str);
int				valid_float(char *str);
int				isnumber(char **str);
int				is_int(char **str);

t_tuple 		parse_coordinates(char *str);
t_rgb255		parse_color(char *str);

t_obj_lst   	*new_obj_node(t_object *obj);
int 			obj_list_add(t_obj_lst **list, t_object *obj);
t_obj_lst   	*obj_lst_last(t_obj_lst *objs);

t_ambient   	get_ambient_data(t_pars *conf);
t_camera    	get_camera_data(t_pars *conf);
t_light_src 	get_light_data(t_pars *conf);
t_obj_lst   	*get_objs_data(t_pars *conf);
t_scene 		*parse_scene(t_pars *conf);

void			put_error(char *str);
void			free_object(t_object *obj);
void			object_fatal(t_obj_lst *lst);


#endif
