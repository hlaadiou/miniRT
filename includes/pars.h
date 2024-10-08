/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 19:59:11 by azgaoua           #+#    #+#             */
/*   Updated: 2024/07/29 12:07:42 by hlaadiou         ###   ########.fr       */
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

# define MAX_ABS_FLOAT 1000.0f

# include "../lib/libft/libft.h"
# include "miniRT.h"

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

typedef t_light	t_light_src;

typedef struct s_obj_lst
{
	t_object			*obj;
	struct s_obj_lst	*next;
	struct s_obj_lst	*prev;
}	t_obj_lst;

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
	float		vsize;
	float		hwidth;
	float		hheight;
	float		pixel_size;
	t_matrix	*transform;
}	t_camera_fn;

typedef struct s_attributes
{
	float	d;
	float	max;
	float	min;
}	t_attributes;

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
int				check_cap(t_ray r, float t, t_object *cy);
t_vector		local_normal_at(t_object *cy, t_point world_point);
t_matrix		*view_transform(t_point from, t_point to, t_vector up);

/* g_collector */

void			*ft_malloc(size_t size);
t_collector		**ft_collector(void);
t_collector		*ft_lstnew_clctr(void *lst);
void			ft_free_collector(t_collector **lst);
void			ft_lst_add_front_clctr(t_collector **lst, t_collector *new);
t_world			*init_world(t_scene *scene);
t_comps			*prepare_computations(t_inter *inter, t_ray ray);
t_color			shade_hit(t_scene *world, t_comps *copms);
t_color			color_at(t_scene *w, t_ray r);
void			render(t_camera_fn c, t_scene *w, mlx_image_t **image);
t_inter			**local_intersect(t_object *cy, t_ray r);

//HLAADIOU
int				check_al(t_pars *conf);
int				check_camera(t_pars *conf);
int				check_light(t_pars *conf);
int				check_objects(t_pars *conf);
int				check_required_elements(t_pars *conf);
int				check_precision(char *str, size_t k);
int				check_magnitude(char *str);

float			ft_atof(char *str);
int				valid_float(char *str);
int				isnumber(char **str);
int				is_int(char **str);

t_light_src		check_light_data(t_pars *conf);
t_object		*check_objs_data(t_pars *conf);
int				normalized_range(t_vector vec);
t_tuple			parse_coordinates(char *str);
t_rgb255		parse_color(char *str);

t_obj_lst		*new_obj_node(t_object *obj);
int				obj_list_add(t_obj_lst **list, t_object *obj);
t_obj_lst		*obj_lst_last(t_obj_lst *objs);

t_ambient		get_ambient_data(t_pars *conf);
t_camera		get_camera_data(t_pars *conf);
t_light_src		get_light_data(t_pars *conf);
t_obj_lst		*get_objs_data(t_pars *conf);

void			put_error(char *str);
void			free_object(t_object *obj);
void			object_fatal(t_obj_lst *lst);

t_scene			*parse_scene(t_pars *conf);
t_pars			*create_conf(int ac, char **av);

void			print_scene(t_scene *scene); // Remove later
void			ft_free_tab(char **tab);
void			free_f_mtx(float **mtx, int size);
void			free_scene(t_scene *scene);
void			ft_declare_freeing(int i);
void			ft_render_progress(int y);
t_camera_fn		set_camera(t_camera cam);
void			set_transformations(t_obj_lst *lst);
t_lst_inter		*intersect_world(t_scene *w, t_ray r);
t_ray			ray_for_pixel(t_camera_fn c, int px, int py);
int32_t			ft_pixel(int32_t r, int32_t g, int32_t b);
t_camera_fn		camera(int hsize, int vsize, float field_of_view);
t_point			get_obj_point(t_object *obj);
float			get_diameter(t_object *obj);
t_lst_inter		*lst_sort(t_lst_inter *lst);

#endif
