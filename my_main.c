/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:34:21 by azgaoua           #+#    #+#             */
/*   Updated: 2024/04/03 11:12:01 by azgaoua          ###   ########.fr       */
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

// t_ray *ray_for_pixel(t_camera_fn c, int px, int py)
// {
//     float world_x;
//     float world_y;
//     t_tuple pixel;

//     world_x = c.hwidth - (px + 0.5) * c.pixel_size;
//     world_y = c.hheight - (py + 0.5) * c.pixel_size;
//     pixel = mtx_tuple_prod(inverse(c.transform), _point(world_x, world_y, -1));
// 	t_point origin = mtx_tuple_prod(inverse(c.transform), _point(0, 0, 0));
// 	t_vector direction = vec_normalize(subtract_tuples(pixel, origin));
//     return _ray(origin, direction);
// }


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
	t_inter **xs = malloc(sizeof(t_inter *) * 2);
	t_obj_lst *obj = w->obj_lst;
	xs[0] = NULL;
	xs[1] = NULL;
	while (obj != NULL)
	{
		if (obj->obj->type == SPHERE)
			xs = intersect_sp(r, obj->obj);
		else if (obj->obj->type == CYLINDER)
			xs = local_intersect(obj->obj, r);
		else if (obj->obj->type == PLANE)
			xs = intersect_pl(r, obj->obj);
		_intersections(&lst, xs);
		obj = obj->next;
	}
	lst = lst_sort(lst);
	return (lst);
}

t_inter    **intersect_pl(t_ray *ray, t_object *plane)
{
    t_roots    root;

    if (fabs(ray->dir.y) < EPSILON)
        return (NULL);
    root.counter = 1;
    root.t1 = (-1 * ray->org.y) / ray->dir.y;
    root.t2 = root.t1;
    return (_intersection(root, plane));
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
	// comps->point.z = roundf(comps->point.z * 1000) / 1000;
	// comps->point.y = roundf(comps->point.y * 1000) / 1000;
	// comps->point.x = roundf(comps->point.x * 1000) / 1000;
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
	float epsilon = 0.0001;
	comps->over_point = add_tuples(comps->point, multiply_tuple_scalar(epsilon, comps->normalv));
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
			// free(r);
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

// int is_shadowed(t_world *w, t_point p)
// {
//     t_vector v;
//     float distance;
//     t_ray *r = NULL;
//     t_inter *h = NULL;
//     t_lst_inter *lst = NULL;

//     // Calculate direction and distance to light source
//     v = subtract_tuples(w->light.position, p);
//     distance = vec_magnitude(v);

//     // Create ray from point to light source
//     r = _ray(p, vec_normalize(v));

//     // Intersect world with ray
//     lst = intersect_world(w, r);

//     // Find closest intersection
//     h = hit(lst);

//     // Check if intersection is valid and not self-shadowed
//     if (h != NULL && h->t < distance - EPSILON)
//     {
//         // Free allocated memory
//         free(r);
//         // free_inter_list(lst);
//         return 1; // Point is shadowed
//     }

//     // Free allocated memory
//     free(r);
//     // free_inter_list(lst);

//     return 0; // Point is not shadowed
// }


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

// typedef struct {
//     float x, y, z;
// } t_vector;

// typedef struct {
//     t_vector org;   // Origin point of the ray
//     t_vector dir;   // Direction of the ray (unit vector)
// } t_ray;

// typedef struct {
//     t_ray *ray;
// } t_object;

// typedef struct {
//     float t;        // Parameter value along the ray where the intersection occurs
//     t_object *obj;  // Pointer to the intersected object
// } t_inter;

t_inter **local_intersect(t_object *cy, t_ray *r) {
    t_inter **inter = malloc(sizeof(t_inter *) * 2);
    if (inter == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    float a = (r->dir.x * r->dir.x) + (r->dir.z * r->dir.z);
    if (fabs(a) < EPSILON || fabs(r->dir.y) < EPSILON) {
        // r is parallel to the cylinder's axis or too close to zero
        free(inter);
        return NULL;
    }
    float b = 2 * ((r->dir.x * r->org.x) + (r->dir.z * r->org.z));
    float c = (r->org.x * r->org.x) + (r->org.z * r->org.z) - 1;
    float discriminant = b * b - 4 * a * c;
    if (discriminant < EPSILON) {
        free(inter);
        return NULL;
    }
    float sqrt_discriminant = sqrt(discriminant);
    float t1 = (-b - sqrt_discriminant) / (2 * a);
    float t2 = (-b + sqrt_discriminant) / (2 * a);
    if (t1 < EPSILON && t2 < EPSILON) {
        free(inter);
        return NULL;
    }
    inter[0] = malloc(sizeof(t_inter));
    inter[1] = malloc(sizeof(t_inter));
    if (inter[0] == NULL || inter[1] == NULL) {
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


// t_inter **local_intersect(t_object *cy, t_r->*r)
// {
// 	t_ray *ray2;
// 	t_ray *ray;
// 	t_inter **inter = malloc(sizeof(t_inter *) * 2);
// 	t_matrix *transform = cy->transform;
// 	ray = transform_ray(r, transform);
// 	ray2 = transform_ray(r, transform);
// 	float a = ray2->dir.x * ray2->dir.x + ray2->dir.z * ray2->dir.z;
// 	if (a < EPSILON || r->dir.y < EPSILON)
// 	{
// 		// free(ray);
// 		// free(ray2);
// 		return (NULL);
// 	}
// 	float b = 2 * ray2->dir.x * ray2->org.x + 2 * ray2->dir.z * ray2->org.z;
// 	float c = ray2->org.x * ray2->org.x + ray2->org.z * ray2->org.z - 1;
// 	float discriminant = b * b - 4 * a * c;
// 	if (discriminant < 0)
// 	{
// 		// free(ray);
// 		// free(ray2);
// 		return (NULL);
// 	}
// 	inter[0] = malloc(sizeof(t_inter));
// 	inter[1] = malloc(sizeof(t_inter));
// 	float t1 =	(-b - sqrt(discriminant)) / (2 * a);
// 	float t2 =	(-b + sqrt(discriminant)) / (2 * a);
// 	if (t1 > t2)
// 	{
// 		float tmp = t1;
// 		t1 = t2;
// 		t2 = tmp;
// 	}
// 	inter[0]->t = t1;
// 	inter[0]->obj = cy;
// 	inter[1]->t = t2;
// 	inter[1]->obj = cy;
// 	if (inter[0]->t > inter[1]->t)
// 	{
// 		float tmp = inter[0]->t;
// 		inter[0]->t = inter[1]->t;
// 		inter[1]->t = tmp;
// 	}
// 	float y0 = ray->org.y + inter[0]->t * ray->dir.y;
// 	if (cy->cy->min < y0 && y0 < cy->cy->max)
// 	{
// 		inter[0]->t = t1;
// 		inter[0]->obj = cy;
// 	}
// 	float y1 = ray->org.y + inter[1]->t * ray->dir.y;
// 	if (cy->cy->min < y1 && y1 < cy->cy->max)
// 	{
// 		// free(ray);
// 		// free(ray2);
// 		inter[0]->t = t2;
// 		inter[0]->obj = cy;
// 	}
// 	if (inter[0]->t <= 0 || inter[1]->t <= 0)
// 	{
// 		// free(inter[0]);
// 		// free(inter[1]);
// 		// free(inter);
// 		// free(ray);
// 		// free(ray2);
// 		return (NULL);
// 	}
// 	printf("t1 = %.2f\n", inter[0]->t);
// 	printf("t2 = %.2f\n", inter[1]->t);
// 	// free(ray);
// 	// free(ray2);
// 	return (inter);
// }

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

// int main ()
// {
// 	t_object *cy = _cylinder(_point(0, 0, 0), _vector(0, 1, 0), 1, 2, 1, _color(1, 0, 0));
// 	t_ray *r = _ray(_point(0, 1.5, -2), vec_normalize(_vector(0, 0, 1)));
// 	t_inter **v = local_intersect(cy, r);
// 	if (v)
// 	{
// 		printf("t1 = %.2f\n", v[0]->t);
// 		printf("t2 = %.2f\n", v[1]->t);
// 	}
// 	else 
// 		printf("no intersection\n");
	
// }

int check_cap(t_ray *r, float t, float y)
{
	float x = r->org.x + (t * r->dir.x);
	float z = r->org.z + (t * r->dir.z);
	if (x * x + z * z > 1)
		return (0);
	if (y > 0)
		return (1);
	else if (compare_f(y, 0))
		return (0);
	return (x * x + z * z <= 1);
}

int main ()
{
	t_object *floor = _plane(_point(0, 0, 0), _vector(0, 1, 0), _color(1, 1, 1));
	floor->specs.specular = 0;
	
	t_object *middle = _cylinder(_point(0, 0, 0), _vector(0, 1, 0), 2, 2, 0, _color(0.1, 1, 0.5));

	t_object *right = _sphere(_point(0, 0, 0), 1, _color(0.5, 1, 0.1));
	right->specs.diffuse = 0.7;
	right->specs.specular = 0.3;
	right->transform = inverse(mtx_multiply(translation(1.5, 0.5, -0.5), scaling_mtx(0.5, 0.5, 0.5)));
	right->transform = inverse(translation(2, 1, 2));
	// set_transform(&right, scaling_mtx(2, 2, 2));

	t_object *left = _sphere(_point(0, 0, 0), 1, _color(1, 0.8, 0.1));
	left->specs.diffuse = 0.7;
	left->specs.specular = 0.3;
	set_transform(&left, mtx_multiply(translation(-1.5, 0.33, -0.75), scaling_mtx(0.33, 0.33, 0.33)));

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
	// w->obj_lst->next->next->next->next->obj = ;
	// w->obj_lst->next->next->next->next->next = malloc(sizeof(t_obj_lst));
	// w->obj_lst->next->next->next->next->next->obj = ;
	// w->obj_lst->next->next->next->next->next->next = NULL;
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

// int main ()
// {
// 	t_world *w = malloc(sizeof(t_world));
// 	w->light = _light(_point(-10, 10, -10), 1.0, _color(1.0, 1.0, 1.0));
// 	t_object *s1 = _sphere(_point(0, 0, 0), 1, _color(0.8, 1.0, 0.6));
// 	s1->specs.diffuse = 0.7;
// 	s1->specs.specular = 0.2;
// 	t_object *s2 = _sphere(_point(0, 0, 0), 0.5, _color(0.8, 1.0, 0.6));
// 	s2->specs.diffuse = 0.7;
// 	s2->specs.specular = 0.2;
// 	s2->transform = scaling_mtx(0.5, 0.5, 0.5);
// 	w->obj_lst = malloc(sizeof(t_obj_lst));
// 	w->obj_lst->obj = s1;
// 	w->obj_lst->next = malloc(sizeof(t_obj_lst));
// 	w->obj_lst->next->obj = s2;
// 	w->obj_lst->next->next = NULL;
// 	// t_camera_fn c = camera(200, 200, M_PI_2);
// 	// c.transform = view_transform(_point(0, 0, -5), _point(0, 0, 0), _vector(0, 1, 0));
// 	// mlx_image_t		*image;
// 	// mlx_t			*mlx;

// 	t_lst_inter *lst = intersect_world(w, _ray(_point(0, 0, -5), _vector(0, 0, 1)));
// 	printf("h->t = %.2f\n", lst->inter->t);
// 	lst  = lst->next;
// 	printf("h->t = %.2f\n", lst->inter->t);
	
	
	
// 	// if (ft_mlx(&mlx, &image) == EXIT_FAILURE)
// 	// 	return (EXIT_FAILURE);
// 	// render(c, w, &image);
// 	// mlx_loop(mlx);
// 	// mlx_terminate(mlx);
// 	// t_ray *r = _ray(_point(0, 0, -5), _vector(0, 0, 1));
// 	// t_color c = color_at(w, r);
	
// }

// int32_t main(void)
// {
// 	mlx_image_t		*image;
// 	mlx_t			*mlx;

// 	if (ft_mlx(&mlx, &image) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);
// 	t_ray		*r = NULL;
// 	t_inter		**xs = NULL;
// 	t_point 	ray_origin = _point(0, 0, -10);
// 	t_point 	position = _point(0, 0, 0); 
// 	float		wall_size = 7;
// 	t_object 	*shape = _sphere(_point(0, 0, 0), 1, _color(1.0, 0.9, 0.9));
// 	shape->transform = scaling_mtx(10, 0.01, 10);
// 	shape->specs.specular = 0;
// 	t_light		light = _light(_point(-10, 10, -10), 1.0, _color(1.0, 1.0, 1.0));
// 	t_point		point;
// 	float	 	world_x = 0;
// 	float	 	world_y = 0;
// 	float 		half = wall_size / 2;
// 	int x;
// 	int y;

// 	for (y = 0; y < HEIGHT; y++)
// 	{
// 		world_y = half - ((float)((float)wall_size/(float )(HEIGHT) * y));
// 		for (x = 0; x < WIDTH; x++)
// 		{
// 			world_x = -half + ((float)((float)wall_size/(float )(WIDTH) * x));
// 			position = _point(world_x, world_y, 10);
// 			r = _ray(ray_origin, vec_normalize(subtract_tuples(position, ray_origin)));
// 			xs = intersect_sp(r, shape);
// 			if (xs && (xs[0]->t > 0 || xs[1]->t > 0))
// 			{
// 				if (xs[0]->t > 0)
// 					point = _position(r, xs[0]->t);
// 				else if (xs[1]->t > 0)
// 					point = _position(r, xs[1]->t);
// 				t_color c = illuminate(shape, point, light, ray_origin);
// 				c = normalizeColor(c);
// 				c = _color255(c);
// 				int32_t color = ft_pixel((int)(c.r), (int)(c.g), \
// 										(int)(c.b), 0x00FF);
// 				mlx_put_pixel(image, x, y, color);
// 			}
// 			// else
// 			// 	mlx_put_pixel(image, x, y, 0x000000FF);

// 			free(r);
// 			free(xs);
// 		}
// 		printf("progress = -----------------> ( %.2f %%) <----------------- \r", \
// 				(float )((float )(x*y)/((float )HEIGHT * ((float )WIDTH - 1))) * 100);
// 		fflush(stdout);
// 	}
// 	ray_origin = _point(0, 0, -10);
// 	position = _point(0, 0, 0); 
// 	wall_size = 7;
// 	shape = _sphere(_point(0, 0, 0), 1, _color(1.0, 0.9, 0.9));
// 	shape->transform = mtx_multiply(scaling_mtx(10, 0.01, 10), mtx_multiply( rotation_x(-M_PI_2),
// 							mtx_multiply(rotation_y(-M_PI_4) ,translation(0, 0, 5))));
// 	shape->specs.specular = 0;
// 	light = _light(_point(-10, 10, -10), 1.0, _color(1.0, 1.0, 1.0));
// 	world_x = 0;
// 	world_y = 0;
// 	half = wall_size / 2;

// 	for (y = 0; y < HEIGHT; y++)
// 	{
// 		world_y = half - ((float)((float)wall_size/(float )(HEIGHT) * y));
// 		for (x = 0; x < WIDTH; x++)
// 		{
// 			world_x = -half + ((float)((float)wall_size/(float )(WIDTH) * x));
// 			position = _point(world_x, world_y, 10);
// 			r = _ray(ray_origin, vec_normalize(subtract_tuples(position, ray_origin)));
// 			xs = intersect_sp(r, shape);
// 			if (xs && (xs[0]->t > 0 || xs[1]->t > 0))
// 			{
// 				if (xs[0]->t > 0)
// 					point = _position(r, xs[0]->t);
// 				else if (xs[1]->t > 0)
// 					point = _position(r, xs[1]->t);
// 				t_color c = illuminate(shape, point, light, ray_origin);
// 				c = normalizeColor(c);
// 				c = _color255(c);
// 				int32_t color = ft_pixel((int)(c.r), (int)(c.g), \
// 										(int)(c.b), 0x00FF);
// 				mlx_put_pixel(image, x, y, color);
// 			}
// 			// else
// 			// 	mlx_put_pixel(image, x, y, 0x000000FF);

// 			free(r);
// 			free(xs);
// 		}
// 		printf("progress = -----------------> ( %.2f %%) <----------------- \r", \
// 				(float )((float )(x*y)/((float )HEIGHT * ((float )WIDTH - 1))) * 100);
// 		fflush(stdout);
// 	}
// 	ray_origin = _point(0, 0, -10);
// 	position = _point(0, 0, 0); 
// 	wall_size = 7;
// 	shape = _sphere(_point(0, 0, 0), 1, _color(1.0, 0.9, 0.9));
// 	shape->transform = mtx_multiply(scaling_mtx(10, 0.01, 10), mtx_multiply( rotation_x(M_PI_2),
// 							mtx_multiply(rotation_y(M_PI_4) ,translation(0, 0, 5))));
// 	shape->specs.specular = 0;
// 	light = _light(_point(-10, 10, -10), 1.0, _color(1.0, 1.0, 1.0));
// 	world_x = 0;
// 	world_y = 0;
// 	half = wall_size / 2;

// 	for (y = 0; y < HEIGHT; y++)
// 	{
// 		world_y = half - ((float)((float)wall_size/(float )(HEIGHT) * y));
// 		for (x = 0; x < WIDTH; x++)
// 		{
// 			world_x = -half + ((float)((float)wall_size/(float )(WIDTH) * x));
// 			position = _point(world_x, world_y, 10);
// 			r = _ray(ray_origin, vec_normalize(subtract_tuples(position, ray_origin)));
// 			xs = intersect_sp(r, shape);
// 			if (xs && (xs[0]->t > 0 || xs[1]->t > 0))
// 			{
// 				if (xs[0]->t > 0)
// 					point = _position(r, xs[0]->t);
// 				else if (xs[1]->t > 0)
// 					point = _position(r, xs[1]->t);
// 				t_color c = illuminate(shape, point, light, ray_origin);
// 				c = normalizeColor(c);
// 				c = _color255(c);
// 				int32_t color = ft_pixel((int)(c.r), (int)(c.g), \
// 										(int)(c.b), 0x00FF);
// 				mlx_put_pixel(image, x, y, color);
// 			}
// 			// else
// 			// 	mlx_put_pixel(image, x, y, 0x000000FF);

// 			free(r);
// 			free(xs);
// 		}
// 		printf("progress = -----------------> ( %.2f %%) <----------------- \r", \
// 				(float )((float )(x*y)/((float )HEIGHT * ((float )WIDTH - 1))) * 100);
// 		fflush(stdout);
// 	}
// 	ray_origin = _point(0, 0, -15);
// 	position = _point(0, 0, 0); 
// 	wall_size = 7;
//  	shape = _sphere(_point(0, 0, 0), 1, _color(0.1, 1, 0.5));
// 	shape->specs.diffuse = 0.7;
// 	shape->specs.specular = 0.3;
// 	shape->transform = translation(0.5, -1, -0.5);
//  	world_x = 0;
//  	world_y = 0;
// 	half = wall_size / 2;
// 	for (y = 0; y < HEIGHT; y++)
// 	{
// 		world_y = half - ((float)((float)wall_size/(float )(HEIGHT) * y));
// 		for (x = 0; x < WIDTH; x++)
// 		{
// 			world_x = -half + ((float)((float)wall_size/(float )(WIDTH) * x));
// 			position = _point(world_x, world_y, 10);
// 			r = _ray(ray_origin, vec_normalize(subtract_tuples(position, ray_origin)));
// 			xs = intersect_sp(r, shape);
// 			if (xs && (xs[0]->t > 0 || xs[1]->t > 0))
// 			{
// 				if (xs[0]->t > 0)
// 					point = _position(r, xs[0]->t);
// 				else if (xs[1]->t > 0)
// 					point = _position(r, xs[1]->t);
// 				t_color c = illuminate(shape, point, light, ray_origin);
// 				c = normalizeColor(c);
// 				c = _color255(c);
// 				int32_t color = ft_pixel((int)(c.r), (int)(c.g), \
// 										(int)(c.b), 0x00FF);
// 				mlx_put_pixel(image, x, y, color);
// 			}
// 			free(r);
// 			free(xs);
// 		}
// 		printf("progress = -----------------> ( %.2f %%) <----------------- \r", \
// 				(float )((float )(x*y)/((float )HEIGHT * ((float )WIDTH - 1))) * 100);
// 		fflush(stdout);
// 	}
// 	// ray_origin = _point(0, 0, -80);
// 	// position = _point(0, 0, 0); 
// 	// shape = _sphere(_point(0, 0, 0), 1, _color(0.0, 1.0, 0.0));
// 	// wall_size = 7;
// 	// shape->transform = translation(0, 2, 0);
//  	// world_x = 0;
//  	// world_y = 0;
// 	// half = wall_size / 2;
// 	// for (y = 0; y < HEIGHT; y++)
// 	// {
// 	// 	world_y = half - ((float)((float)wall_size/(float )(HEIGHT) * y));
// 	// 	for (x = 0; x < WIDTH; x++)
// 	// 	{
// 	// 		world_x = -half + ((float)((float)wall_size/(float )(WIDTH) * x));
// 	// 		position = _point(world_x, world_y, 10);
// 	// 		r = _ray(ray_origin, vec_normalize(subtract_tuples(position, ray_origin)));
// 	// 		xs = intersect_sp(r, shape);
// 	// 		if (xs && (xs[0]->t > 0 || xs[1]->t > 0))
// 	// 		{
// 	// 			if (xs[0]->t > 0)
// 	// 				point = _position(r, xs[0]->t);
// 	// 			else if (xs[1]->t > 0)
// 	// 				point = _position(r, xs[1]->t);
// 	// 			t_color c = illuminate(shape, point, light, ray_origin);
// 	// 			c = normalizeColor(c);
// 	// 			c = _color255(c);
// 	// 			int32_t color = ft_pixel((int)(c.r), (int)(c.g), \
// 	// 									(int)(c.b), 0x00FF);
// 	// 			mlx_put_pixel(image, x, y, color);
// 	// 		}
// 	// 		free(r);
// 	// 		free(xs);
// 	// 	}
// 	// 	printf("progress = -----------------> ( %.2f %%) <----------------- \r", \
// 	// 			(float )((float )(x*y)/((float )HEIGHT * ((float )WIDTH - 1))) * 100);
// 	// 	fflush(stdout);
// 	// }
// 	mlx_loop_hook(mlx, ft_hook, mlx);
// 	system("clear");
// 	fflush(stdout);
// 	printf("DONE !!\r");
// 	fflush(stdout); 
// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }

