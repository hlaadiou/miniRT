/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:34:21 by azgaoua           #+#    #+#             */
/*   Updated: 2024/07/25 22:12:09 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/miniRT.h"
#include "includes/pars.h"
#include "includes/geometry.h"


int32_t	ft_pixel(int32_t r, int32_t g, int32_t b)
{
	return (r << 24 | g << 16 | b << 8 | 0xFF);
}

void	ft_hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

int	ft_mlx(mlx_t **mlx, mlx_image_t **image)
{
	int	w;
	int	h;

	w = WIDTH;
	h = HEIGHT;
	if (!((*mlx) = mlx_init(w, h, "miniRT", false)))
	{
		puts(mlx_strerror(mlx_errno)); // Not allowed !
		return (EXIT_FAILURE);
	}
	if (!((*image) = mlx_new_image(*mlx, w, h)))
	{
		mlx_close_window(*mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (mlx_image_to_window((*mlx), (*image), 0, 0) == -1)
	{
		mlx_close_window(*mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

t_camera_fn	camera(int hsize, int vsize, float field_of_view)
{
	t_camera_fn	c;
	float		aspect;
	float		hview;

	c.vsize = vsize;
	c.hsize = hsize;
	if (field_of_view >= (179.5f * (M_PI / 180)))
		field_of_view = 179.5f * (M_PI / 180);
	hview = tan(field_of_view / 2.0f);
	aspect = (float)hsize / (float)vsize;
	if (aspect >= 1.0f)
	{
		c.hwidth = hview;
		c.hheight = hview / aspect;
	}
	else
	{
		c.hwidth = hview * aspect;
		c.hheight = hview;
	}
	c.pixel_size = (c.hwidth * 2.0f) / hsize;
	return (c);
}

t_ray ray_for_pixel(t_camera_fn c, int px, int py)
{
	float		world_x;
	float		world_y;
	t_tuple		pixel;

	world_x = c.hwidth - (px + 0.5) * c.pixel_size;
	world_y = c.hheight - (py + 0.5) * c.pixel_size;
	pixel = mtx_tuple_prod(c.transform, _point(world_x, world_y, -1));
	return (_ray(mtx_tuple_prod(c.transform, _point(0, 0, 0)), \
			vec_normalize(subtract_tuples(pixel, \
				mtx_tuple_prod(c.transform, _point(0, 0, 0))))));
}

void print_lst(t_lst_inter *lst)
{
	t_lst_inter *tmp = lst;

	while (tmp)
	{
		if (tmp && tmp->inter && tmp->inter->t > 20)
		{
			// printf("t = %.2f\n", tmp->inter->t);
			// printf("lst *obj = %p\n", tmp->inter->obj);
		}
		tmp = tmp->next;
	}
}

t_lst_inter *lst_sort(t_lst_inter *lst)
{
	t_lst_inter	*tmp;
	t_lst_inter	*tmp2;
	t_inter		*inter;

	tmp = lst;
	tmp2 = lst;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (tmp->inter && tmp2->inter && tmp->inter->t > tmp2->inter->t)
			{
				inter = tmp->inter;
				tmp->inter = tmp2->inter;
				tmp2->inter = inter;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	// printf("*****start*****\n");
	// print_lst(lst);
	// printf("*****end*****\n");
	return (lst);
}

t_lst_inter *intersect_world(t_scene *w, t_ray r)
{
	t_lst_inter	*lst;
	t_inter		**xs;
	t_obj_lst	*obj;
	t_ray		r1;

	xs = NULL;
	lst = NULL;
	obj = w->lst;
	while (obj != NULL)
	{
		if (obj->obj->type == PLANE)
			xs = intersect_pl(r, obj->obj);
		else if (obj->obj->type == CYLINDER) /* r1 to be testet for remouving it AYGAOUA  */
		{
			r1 = transform_ray(r, obj->obj->transform);
			xs = intersect_caps(obj->obj, r1);
			if (xs)
				_intersections(&lst, xs);
			xs = local_intersect(obj->obj, r1);
		}
		else if (obj->obj->type == SPHERE)
			xs = intersect_sp(r, obj->obj);
		if (xs)
			_intersections(&lst, xs);
		obj = obj->next;
	}
	lst = lst_sort(lst);
	return (lst);
}

t_comps	*prepare_computations(t_inter *inter, t_ray ray)
{
	t_comps	*comps;

	comps = ft_malloc(sizeof(t_comps));
	comps->inside = -1;
	comps->t = inter->t;
	comps->obj = inter->obj;
	comps->point = _position(ray, comps->t);
	comps->eyev = multiply_tuple_scalar(-1, ray.dir);
	if (comps->obj->type == SPHERE)
		comps->normalv = normal_at(comps->obj, comps->point);
	else if (comps->obj->type == CYLINDER)
		comps->normalv = local_normal_at(comps->obj, comps->point);
	else if (comps->obj->type == PLANE)
		comps->normalv = comps->obj->pl->vec;
	if (dot_product(comps->normalv, comps->eyev) < 0 && fabs(dot_product(comps->normalv, comps->eyev)) > 0.5f)
	{
		comps->inside = 1;
		comps->normalv = multiply_tuple_scalar(-1, comps->normalv);
	}
	else
		comps->inside = 0;
	if (((comps->obj->type == SPHERE && (comps->obj->sp->radius * comps->t) >= 3.0f) || \
			(comps->obj->type == CYLINDER && \
			((comps->obj->cy->diameter / 2) * comps->t) >= 3.0f)) && comps->inside == 0)
	{
		comps->point = add_tuples(comps->point, \
						multiply_tuple_scalar(EPSILON, comps->normalv));
	}
	else
	{
		comps->point = add_tuples(comps->point, \
							multiply_tuple_scalar(0.00001f, comps->normalv));
	}
	// if (comps->inside)
	// 	printf("inside = %.2f\n", dot_product(comps->normalv, comps->eyev));
	return (comps);
}

t_color	color_at(t_scene *w, t_ray r)
{
	t_lst_inter	*lst;
	t_inter		*h;
	t_comps		*comps;
	t_color		color;

	lst = intersect_world(w, r);
	h = hit(lst);
	if (h == NULL || (h->obj && compare_f(h->t, 0.0f)) || h->obj == NULL)
		return (_color(0, 0, 0));
	comps = prepare_computations(h, r);
	color = shade_hit(w, comps);
	return (color);
}

t_color shade_hit(t_scene *world, t_comps *copms)
{
	int	shadowed;

	shadowed = is_shadowed(world, copms->point);
	return (illuminate(copms, world->light, shadowed));
}

t_color normalize_color(t_color colorValue)
{
	float	max_val;

	max_val = fmax(colorValue.r, fmax(colorValue.g, colorValue.b));
	if (max_val > 1)
	{
		colorValue.r = colorValue.r / max_val;
		colorValue.g = colorValue.g / max_val;
		colorValue.b = colorValue.b / max_val;
		return (colorValue);
	}
	return (colorValue);
}

void	render(t_camera_fn c, t_scene *w, mlx_image_t **image)
{
	t_ray		r;
	t_color		color;
	int32_t		color_int;
	int			y;
	int			x;

	y = -1;
	printf("\n");
	while (++y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			r = ray_for_pixel(c, x, y);
			color = color_at(w, r);
			color = normalize_color(color);
			if (w->light.brightness != 0)
				color = multiply_color_scalar(w->light.brightness, color);
			color = _color255(color);
			color_int = ft_pixel((int)(color.r), (int)(color.g), \
										(int)(color.b));
			mlx_put_pixel((*image), x, y, color_int);
			x++;
		}
		if (((float)((y *100)/ HEIGHT)) > 20.0f)
			printf("\r##--------");
		if (((float)((y *100)/ HEIGHT) * 100) > 40.0f)
		    printf("\r####------");
		if (((float)((y *100)/ HEIGHT) * 100) > 60.0f)
		    printf("\r######----");
		if (((float)((y *100)/ HEIGHT) * 100) > 80.0f)
		    printf("\r########--");
		if (((float)((y *100)/ HEIGHT) * 100) > 100.0f)
			printf("\r##########");
		
	}
}

t_matrix	*view_transform(t_point from, t_point to, t_vector up)
{
	t_matrix		*orientation;
	t_matrix		*translation_mtx;
	t_matrix		*res;
	t_vector		left;
	t_vector		forward;

	if (compare_f(up.x, fabs(subtract_tuples(to, from).x)) && \
		compare_f(up.y, fabs(subtract_tuples(to, from).y)) && \
		compare_f(up.z, fabs(subtract_tuples(to, from).z)))
	{
		if (subtract_tuples(to, from).y < EPSILON)
			up = _vector(0, 0, 1);
		else
			up = _vector(0, 0, -1);
	}
	forward = vec_normalize(subtract_tuples(to, from));
	up = vec_normalize(up);
	left = cross_product(forward, up);
	up = cross_product(left, forward);
	orientation = _identity(4);
	orientation->mtx[0][0] = left.x;
	orientation->mtx[0][1] = left.y;
	orientation->mtx[0][2] = left.z;
	orientation->mtx[1][0] = up.x;
	orientation->mtx[1][1] = up.y;
	orientation->mtx[1][2] = up.z;
	orientation->mtx[2][0] = -forward.x;
	orientation->mtx[2][1] = -forward.y;
	orientation->mtx[2][2] = -forward.z;
	translation_mtx = translation(-from.x, -from.y, -from.z);
	res = mtx_multiply(orientation, translation_mtx);
	return (res);
}

void	free_f_mtx(float **mtx, int size)
{
	while (size)
	{
		free(mtx[size - 1]);
		size--;
	}
	free(mtx);
}

int	compare_ff(float a, float b)
{
	if (fabs(a - b) < 0.000001f)
		return (1);
	else
		return (0);
}

int	is_shadowed(t_scene *w, t_point p)
{
	t_vector		v;
	float			distance;
	t_ray			r;
	t_inter			*h;
	t_lst_inter		*lst;

	v = subtract_tuples(w->light.position, p);
	distance = vec_magnitude(v);
	r = _ray(p, vec_normalize(v));
	lst = intersect_world(w, r);
	h = hit(lst);
	if (h != NULL && (compare_ff(fabs(h->t - distance), 0)))
		return (1);
	if (h != NULL && (h->t < distance))
		return (1);
	return (0);
}

t_camera_fn	set_camera(t_camera cam)
{
	t_camera_fn	c;

	c = camera(WIDTH, HEIGHT, cam.fov * (M_PI / 180));
	c.transform = inverse(view_transform(cam.view_point, \
					add_tuples(cam.view_point, cam.orientation), \
					_point(0, 1, 0)));
	return (c);
}

t_point	get_obj_point(t_object *obj)
{
	if (obj->type == SPHERE)
		return (obj->sp->org);
	else if (obj->type == CYLINDER)
		return (obj->cy->center);
	else if (obj->type == PLANE)
		return (obj->pl->pt);
	return ((t_point){0});
}

float	get_diameter(t_object *obj)
{
	if (obj->type == SPHERE)
		return (obj->sp->radius);
	else if (obj->type == CYLINDER)
		return (obj->cy->diameter);
	return (1.0);
}

t_matrix	*axis_to_matrix(t_vector up, t_vector forw, t_vector right)
{
	t_matrix	*res;

	res = _identity(4);
	res->mtx[0][0] = up.x;
	res->mtx[1][0] = up.y;
	res->mtx[2][0] = up.z;
	res->mtx[0][1] = forw.x;
	res->mtx[1][1] = forw.y;
	res->mtx[2][1] = forw.z;
	res->mtx[0][2] = right.x;
	res->mtx[1][2] = right.y;
	res->mtx[2][2] = right.z;
	return (res);
}

t_matrix	*axis_cylinder(t_vector orie)
{
	t_vector	up;
	t_vector	forw;
	t_vector	right;

	if (orie.x == 0 && orie.z == 0)
	{
		if (orie.y >= 0)
		{
			up = _vector(0, 1, 0);
			right = _vector(1, 0, 0);
		}
		else
		{
			up = _vector(0, -1, 0);
			right = _vector(-1, 0, 0);
		}
		forw = _vector(0, 0, 1);
	}
	else
	{
		up = vec_normalize(orie); /* to removed !!*/
		forw = vec_normalize(cross_product(_vector(0, 1, 0), up));
		right = cross_product(up, forw);
	}
	return (axis_to_matrix(right, up, forw));
}

void	set_transformations(t_obj_lst *lst)
{
	t_point		p;
	float		scale;

	p = _point(0, 0, 0);
	while (lst)
	{
		p = get_obj_point(lst->obj);
		scale = get_diameter(lst->obj);
		scale = scale / 2.0f;
		if (lst->obj->type == SPHERE)
		{
			lst->obj->sp->org = _point(0, 0, 0);
			lst->obj->sp->radius = 1;
			lst->obj->transform = inverse(translation(p.x, p.y, p.z));
			set_transform(&lst->obj, inverse(scaling_mtx(scale, scale, scale)));
		}
		else if (lst->obj->type == CYLINDER)
		{
			lst->obj->cy->center = _point(0, 0, 0);
			lst->obj->transform = _identity(4);
			set_transform(&lst->obj, inverse(translation(p.x, p.y, p.z)));
			set_transform(&lst->obj, \
							inverse(axis_cylinder(lst->obj->cy->axis)));
		}
		lst = lst->next;
	}
	return ;
}

void	vv(void)
{
	system("leaks miniRT");
}

int	main(int ac, char **av)
{
	mlx_image_t		*image;
	mlx_t			*mlx;
	t_pars			*conf;
	t_scene			*scene;
	t_camera_fn		cam;

	// atexit (vv);
	conf = create_conf(ac, av);
	if (!conf)
		return (1);
	scene = parse_scene(conf);
	if (!scene)
		return (1);
	if (ft_mlx(&mlx, &image) == EXIT_FAILURE)
		return (1);
	cam = set_camera(scene->camera);
	set_transformations(scene->lst);
	render(cam, scene, &image);
	printf("done\n");
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	ft_free_collector(ft_collector());
	return (0);
}
