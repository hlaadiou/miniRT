/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:34:21 by azgaoua           #+#    #+#             */
/*   Updated: 2024/05/02 15:52:00 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/miniRT.h"

# define WIDTH  200
# define HEIGHT 100

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

int ft_mlx(mlx_t **mlx, mlx_image_t **image)
{
	if (!((*mlx) = mlx_init(WIDTH, HEIGHT, "miniRT", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!((*image) = mlx_new_image((*mlx), WIDTH, HEIGHT)))
	{
		mlx_close_window(*mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window((*mlx), (*image), 0, 0) == -1)
	{
		mlx_close_window(*mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_struct(t_pars *pars)
{
	t_pars	*tmp;

	while (pars)
	{
		tmp = pars;
		pars = pars->next;
		if (tmp->elements)
			ft_free_tab(tmp->elements);
		free(tmp);
	}
}

t_color normalizeColor(t_color colorValue) {
	float max_val = fmax(colorValue.r, fmax(colorValue.g, colorValue.b));
	if (max_val > 1.0f) {
        colorValue.r = colorValue.r / max_val;
		colorValue.g = colorValue.g / max_val;
		colorValue.b = colorValue.b / max_val;
		return (colorValue);
    }
	return colorValue;
}

t_camera_fn camera(int hsize, int vsize, float field_of_view)
{
	t_camera_fn c;
	float aspect;
	float hview;

	c.vsize = vsize;
	c.hsize = hsize;
	hview = tan(field_of_view / 2);
	aspect = (float)hsize / (float)vsize;
	if (aspect >= 1)
	{
		c.hwidth = hview;
		c.hheight = hview / aspect;
	}
	else
	{
		c.hwidth = hview * aspect;
		c.hheight = hview;
	}
	c.pixel_size = (c.hwidth * 2) / hsize;
	c.transform = _identity(4);
	return c;
}

t_ray *ray_for_pixel(t_camera_fn c, int px, int py)
{
	float world_x;
	float world_y;
	t_tuple pixel;

	world_x = c.hwidth - (px + 0.5) * c.pixel_size;
	world_y = c.hheight - (py + 0.5) * c.pixel_size;
	pixel = mtx_tuple_prod(inverse(c.transform), _point(world_x, world_y, -1));
	return (_ray(mtx_tuple_prod(inverse(c.transform), _point(0, 0, 0)), \
			vec_normalize(subtract_tuples(pixel, \
			mtx_tuple_prod(inverse(c.transform), _point(0, 0, 0))))));
}

t_lst_inter *lst_sort(t_lst_inter *lst)
{
	t_lst_inter *tmp = lst;
	t_lst_inter *tmp2 = lst;
	t_inter *inter;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (tmp->inter->t > tmp2->inter->t)
			{
				inter = tmp->inter;
				tmp->inter = tmp2->inter;
				tmp2->inter = inter;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return (lst);

}

t_lst_inter *intersect_world(t_world *w, t_ray *r)
{
	t_lst_inter *lst = NULL;
	t_inter **xs = NULL;
	t_obj_lst *obj = w->obj_lst;
	while (obj != NULL)
	{
		if (obj->obj->type == SPHERE)
			xs = intersect_sp(r, obj->obj);
		else if (obj->obj->type == CYLINDER)
		{
			xs = intersect_caps(obj->obj, r);
			_intersections(&lst, xs);
			xs = local_intersect(obj->obj, r);
		}
		else if (obj->obj->type == PLANE)
			xs = intersect_pl(r, obj->obj);
		if (xs)
			_intersections(&lst, xs);
		obj = obj->next;
	}
	lst = lst_sort(lst);
	return (lst);
}

t_comps *prepare_computations(t_inter *inter, t_ray *ray)
{
	t_comps	*comps;

	comps = malloc(sizeof(t_comps));
	if (!comps)
		return (NULL);
	comps->t = inter->t;
	comps->obj = inter->obj;
	comps->point = _position(ray, comps->t);
	comps->eyev = multiply_tuple_scalar(-1, ray->dir);
	if (comps->obj->type == SPHERE)
		comps->normalv = normal_at(comps->obj, comps->point);
	else if (comps->obj->type == CYLINDER)
		comps->normalv = local_normal_at(comps->obj, comps->point);
	if (dot_product(comps->normalv, comps->eyev) < 0)
	{
		comps->inside = 1;
		comps->normalv = multiply_tuple_scalar(-1, comps->normalv);
	}
	else
		comps->inside = 0;
	comps->over_point = add_tuples(comps->point, multiply_tuple_scalar(EPSILON, comps->normalv));
	return (comps);
}

t_color color_at(t_world *w, t_ray *r)
{
	t_lst_inter *lst;
	lst = intersect_world(w, r);
	t_inter *h;
	h = hit(lst);
	if (h == NULL)
		return (_color(0, 0, 0));
	t_comps *comps = prepare_computations(h, r);
	t_color color = shade_hit(w, comps);
	return (color);
}

t_color shade_hit(t_world *world, t_comps *copms)
{
	int shadowed;
	shadowed = is_shadowed(world, copms->point);
	return(illuminate(copms->obj, copms->point, world->light, copms->eyev, shadowed));
}

void render(t_camera_fn c, t_world *w, mlx_image_t **image)
{	
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			t_ray *r = ray_for_pixel(c, x, y);
			t_color color = color_at(w, r);
			color = normalizeColor(color);
			if (w->light.brightness != 0)
				color = multiply_color_scalar(w->light.brightness, color);
			color = _color255(color);
			int32_t color_int = ft_pixel((int)(color.r), (int)(color.g), \
										(int)(color.b), 0x00FF);
			mlx_put_pixel((*image), x, y, color_int);
		}

	}
}

t_matrix *view_transform(t_point from, t_point to, t_vector up)
{
	t_vector forward = vec_normalize(subtract_tuples(to, from));
	t_vector upn = vec_normalize(up);
	t_vector left = cross_product(forward, upn);
	t_vector true_up = cross_product(left, forward);
	t_matrix *orientation = _identity(4);
	orientation->mtx[0][0] = left.x;
	orientation->mtx[0][1] = left.y;
	orientation->mtx[0][2] = left.z;
	orientation->mtx[1][0] = true_up.x;
	orientation->mtx[1][1] = true_up.y;
	orientation->mtx[1][2] = true_up.z;
	orientation->mtx[2][0]= -forward.x;
	orientation->mtx[2][1]= -forward.y;
	orientation->mtx[2][2] = -forward.z;
	t_matrix *translation_mtx = translation(-from.x, -from.y, -from.z);
	t_matrix *res = mtx_multiply(orientation, translation_mtx);
	free(orientation->mtx);
	free(orientation);
	free(translation_mtx->mtx);
	free(translation_mtx);
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

int	is_shadowed(t_world *w, t_point p)
{
	t_vector v;
	float distance;
	t_ray *r = NULL;
	t_inter *h = NULL;
	t_lst_inter *lst = NULL;

	v = subtract_tuples(w->light.position, p);
	distance = vec_magnitude(v);
	r = _ray(p, vec_normalize(v));
	lst = intersect_world(w, r);
	h = hit(lst);
	if (h != NULL && h->t < distance - EPSILON)
	{
		free(r);
		return (1);
	}
	free(r);
	return (0);
}

t_ray *transform_ray(t_ray *ray, t_matrix *a)
{
	t_ray *b;

	b = _ray(ray->org, ray->dir);
	b->org =  mtx_tuple_prod(a, ray->org);
	b->dir =  mtx_tuple_prod(a, ray->dir);
	return (b);
}

t_inter **local_intersect(t_object *cy, t_ray *r) {
    t_inter **inter = malloc(sizeof(t_inter *) * 2);
    if (inter == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    float a = (r->dir.x * r->dir.x) + (r->dir.z * r->dir.z);
    if (fabs(a) < EPSILON || fabs(r->dir.y) < EPSILON) 
	{
        free(inter);
        return (NULL);
    }
    float b = 2 * ((r->dir.x * r->org.x) + (r->dir.z * r->org.z));
    float c = (r->org.x * r->org.x) + (r->org.z * r->org.z) - 1;
    float discriminant = b * b - 4 * a * c;
    if (discriminant < EPSILON)
	{
        free(inter);
        return (NULL);
    }
    float sqrt_discriminant = sqrt(discriminant);
    float t1 = (-b - sqrt_discriminant) / (2 * a);
    float t2 = (-b + sqrt_discriminant) / (2 * a);
    if (t1 < EPSILON && t2 < EPSILON)
	{
        free(inter);
        return (NULL);
    }
    inter[0] = malloc(sizeof(t_inter));
    inter[1] = malloc(sizeof(t_inter));
    if (inter[0] == NULL || inter[1] == NULL)
	{
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
	if (t1 > t2)
	{
		float tmp = t1;
		t1 = t2;
		t2 = tmp;
	}
	float y0 = r->org.y + t1 * r->dir.y;
	if (cy->cy->min < y0 && y0 < cy->cy->max)
	{
		inter[0]->t = t1;
		inter[0]->obj = cy;
	}
	float y1 = r->org.y + t2 * r->dir.y;
	if (cy->cy->min < y1 && y1 < cy->cy->max)
	{
		inter[1]->t = t2;
		inter[1]->obj = cy;
	}
    return inter;
}

t_vector	local_normal_at(t_object *cy, t_point world_point)
{
	float dist = (world_point.x * world_point.x) + (world_point.z * world_point.z);
	if (dist < 1 && world_point.y >= cy->cy->max)
		return (_vector(0, 1, 0));
	else if (dist < 1 && world_point.y <= cy->cy->min)
		return (_vector(0, -1, 0));
	else
		return (_vector(world_point.x, 0, world_point.z));
}

int check_cap(t_ray *r, float t)
{
	float x = r->org.x + (t * r->dir.x);
	float z = r->org.z + (t * r->dir.z);
	return (x * x + z * z <= 1);
}

t_inter **intersect_caps(t_object *cy, t_ray *r)
{
	t_inter **inter = malloc(sizeof(t_inter *) * 2);
	inter[0] = malloc(sizeof(t_inter));
	inter[1] = malloc(sizeof(t_inter));
	if (inter[0] == NULL || inter[1] == NULL || inter == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	if (compare_f(r->dir.y, 0))
		return (NULL);
	float t = (cy->cy->min - r->org.y) / r->dir.y;
	if (check_cap(r, t))
	{
		inter[0]->t = t;
		inter[0]->obj = cy;
	}
	t = (cy->cy->max - r->org.y) / r->dir.y;
	if (check_cap(r, t))
	{
		inter[1]->t = t;
		inter[1]->obj = cy;
	}
	return (inter);
}

t_inter    **intersect_pl(t_ray *ray, t_object *plane)
{
    t_inter        **inter;
    t_roots        roots;
    t_vector    x;
    float        prod;

    inter = NULL;
    if (!dot_product(ray->dir, plane->pl->vec))
        return (NULL);
    x = subtract_tuples(ray->org, plane->pl->pt);
    prod = dot_product(ray->dir, plane->pl->vec) * dot_product(x, plane->pl->vec);
    if (prod < 0.0)
    {
        roots.counter = 1;
        roots.t1 = dot_product(multiply_tuple_scalar(-1.0, x), plane->pl->vec) \
        / dot_product(ray->dir, plane->pl->vec);
        roots.t2 = roots.t1;
        inter = _intersection(roots, plane);
    }
    return (inter);
}

int main ()
{
	t_object *floor = _plane(_point(3, 0, 0), _vector(0, 1, 0), _color(1, 1, 1));
	
	t_object *middle = _cylinder(_point(0, 0, 0), _vector(0, 0, 0), 1, 1, 0, _color(0.1, 1, 0.5));

	t_object *right = _sphere(_point(0, 0, 0), 1, _color(0.5, 1, 0.1));
	right->specs.diffuse = 0.7;
	right->specs.specular = 0.3;

	right->transform = inverse(translation(2, 1, 2));

	t_object *left = _sphere(_point(0, 0, 0), 1, _color(1, 0.8, 0.1));
	left->specs.diffuse = 0.7;
	left->specs.specular = 0.3;
	left->transform = inverse(mtx_multiply(translation(-1.5, 0.33, -0.75), scaling_mtx(0.33, 0.33, 0.33)));

	t_world *w = malloc(sizeof(t_world));
	w->light = _light(_point(-10, 10, -10), 1, _color(1.0, 1.0, 1.0));
	w->obj_lst = malloc(sizeof(t_obj_lst));
	w->obj_lst->obj = floor;
	w->obj_lst->next = malloc(sizeof(t_obj_lst));
	w->obj_lst->next->obj = middle;
	w->obj_lst->next->next = malloc(sizeof(t_obj_lst));
	w->obj_lst->next->next->obj = right;
	w->obj_lst->next->next->next = malloc(sizeof(t_obj_lst));
	w->obj_lst->next->next->next->obj = left;
	w->obj_lst->next->next->next->next = NULL;
	t_camera_fn c = camera(WIDTH, HEIGHT, M_PI / 3);
	c.transform = view_transform(_point(0, 1.5, -5), _point(0, 1, 0), _vector(0, 1, 0));

	mlx_image_t *image;
	mlx_t *mlx;
	if (ft_mlx(&mlx, &image) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	render(c, w, &image);
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
