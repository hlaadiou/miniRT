/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:03:30 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/07/18 17:16:41 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

//5 params
// typedef struct s_cylinder
// {
// 	t_point		center;
// 	t_vector	axis;
// 	float		diameter;
// 	float		min;
// 	float		max;
// }	t_cylinder;
t_object	*_cylinder(t_point pt, t_vector axis, float d, float max,float min, t_color c)
{
	t_cylinder	*cy;

	cy = (t_cylinder *)ft_malloc(sizeof(t_cylinder));
	if (!cy)
		return (NULL);
	*cy = (t_cylinder){pt, axis, d, min, max};
	return (_obj(cy, c, CYLINDER));
}

t_inter    **intersect_pl(t_ray ray, t_object *plane)
{
    t_inter         **inter;
    t_roots         roots;
    t_vector        x;
    float           prod;

    inter = NULL;
    if (!dot_product(ray.dir, plane->pl->vec))
        return (NULL);
    x = subtract_tuples(ray.org, plane->pl->pt);
    prod = dot_product(ray.dir, plane->pl->vec) * dot_product(x, plane->pl->vec);
    if (prod < EPSILON)
    {
        roots.counter = 1;
        roots.t1 = dot_product(multiply_tuple_scalar(-1.0, x), plane->pl->vec) \
        / dot_product(ray.dir, plane->pl->vec);
        roots.t2 = roots.t1;
        inter = _intersection(roots, plane);
    }
    return (inter);
}

t_inter **intersect_caps(t_object *cy, t_ray r) {
    t_inter **inter = ft_malloc(sizeof(t_inter *) * 2);
    float t;
    int count = 0;

    if (inter == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    inter[0] = ft_malloc(sizeof(t_inter));
    inter[1] = ft_malloc(sizeof(t_inter));

    if (inter[0] == NULL || inter[1] == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    if (compare_f(r.dir.y, EPSILON)) {
        // free(inter[0]);
        // free(inter[1]);
        // free(inter);
        return NULL;
    }

    // Check intersection with the lower cap
    t = (cy->cy->min - r.org.y) / r.dir.y;
    if (check_cap(r, t, cy)) {
        inter[count]->t = t;
        inter[count]->obj = cy;
        count++;
    }

    // Check intersection with the upper cap
    t = (cy->cy->max - r.org.y) / r.dir.y;
    if (check_cap(r, t, cy)) {
        inter[count]->t = t;
        inter[count]->obj = cy;
        count++;
    }

    // If there are no valid intersections, free memory and return NULL
    if (count == 0) {
        // free(inter[0]);
        // free(inter[1]);
        // free(inter);
        return NULL;
    }

    // If there is only one valid intersection, free the unused allocation
    if (count == 1) {
        // free(inter[1]);
        inter[1] = NULL; // Set the unused slot to NULL for clarity
    }

    return inter;
}

int check_cap(t_ray r, float t, t_object *cy)
{
    float x;
    float z;;

    x = r.org.x + (t * r.dir.x);
    z = r.org.z + (t * r.dir.z);
    if (((x * x) + (z * z)) <= (powf(cy->cy->diameter, 2) / 4.0f))
        return (1);
    return (0);
}

t_vector local_normal_at(t_object *cy, t_point world_point)
{
    t_point object_point;
    t_vector normal;
    float dist;


    object_point = mtx_tuple_prod(cy->transform, world_point);
    dist = powf(object_point.x, 2) + powf(object_point.z, 2);
    if (dist < 1 && object_point.y >= cy->cy->max - EPSILON)
    {
        normal = (t_vector){0, 1, 0, 1};
        normal = mtx_tuple_prod(mtx_transpose(cy->transform), normal);
    }
    else if (dist < 1 && object_point.y <= cy->cy->min + EPSILON)
    {
        normal = (t_vector){0, -1, 0, 1};
        normal = mtx_tuple_prod(mtx_transpose(cy->transform), normal);
    }
    else
    {
        normal = (t_vector){object_point.x, 0, object_point.z, 1};
        normal = mtx_tuple_prod(mtx_transpose(cy->transform), normal);
    }
    return (normal);
}
