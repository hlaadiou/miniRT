/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:34:21 by azgaoua           #+#    #+#             */
/*   Updated: 2024/05/18 21:38:56 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/miniRT.h"

# define WIDTH  800
# define HEIGHT 400

/**
 * @brief Creates a 32-bit pixel color value from the specified red, green, and blue color components.
 * 
 * This function creates a 32-bit pixel color value from the specified red, green, and blue color components.
 * The color components are combined into a single integer value with the red component in the most significant 8 bits,
 * the green component in the middle 8 bits, and the blue component in the least significant 8 bits.
 * The alpha component (transparency) is set to 0xFF (fully opaque).
 * 
 * @param r The red color component value (0-255)
 * @param g The green color component value (0-255)
 * @param b The blue color component value (0-255)
 * 
 * @return The 32-bit pixel color value with the specified color components
 */
int32_t ft_pixel(int32_t r, int32_t g, int32_t b)
{
    return (r << 24 | g << 16 | b << 8 | 0xFF);
}

/**
 * @brief Handles the hook function for the mlx window
 * 
 * This function is responsible for handling the hook function for the mlx window. 
 * It checks if the escape key is pressed and closes the window if it is.
 * 
 * @param param A pointer to the mlx structure for the window
 */
void ft_hook(void* param)
{
    mlx_t* mlx = param;

    if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
        mlx_close_window(mlx);
}

/**
 * @brief Initializes the mlx window and image for rendering
 * 
 * This function initializes the mlx window and image for rendering the miniRT scene.
 * It creates a new mlx window with the specified width and height, and a new image for rendering the scene.
 * 
 * @param mlx A pointer to a pointer to the mlx structure for the window
 * @param image A pointer to a pointer to the mlx_image structure for the rendered image
 * 
 * @return EXIT_SUCCESS if the initialization is successful, EXIT_FAILURE otherwise
 */
int ft_mlx(mlx_t **mlx, mlx_image_t **image)
{
    int w = WIDTH;
    int h = HEIGHT;
    if (!((*mlx) = mlx_init(w, h, "miniRT", true))) 
    {
        puts(mlx_strerror(mlx_errno));  
        return(EXIT_FAILURE);  
    }
    if (!((*image) = mlx_new_image((*mlx), w, h))) 
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

/**
 * @brief Frees the memory allocated for the elements of a string array and the array itself
 * 
 * This function frees the memory allocated for the elements of a string array and the array itself.
 * It iterates through the string array and frees the memory allocated for each element, and then frees the memory allocated for the array itself.
 * 
 * @param tab A pointer to the string array to be freed
 */
void ft_free_tab(char **tab)
{
    int i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

/**
 * @brief Frees the memory allocated for the elements of a linked list and the list nodes
 * 
 * This function frees the memory allocated for the elements of a linked list and the list nodes.
 * It iterates through the linked list and frees the memory allocated for each element and the corresponding list node.
 * 
 * @param pars A pointer to the head of the linked list
 */
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

/**
 * @brief Normalizes the color values to ensure they are within the valid range
 * 
 * This function normalizes the color values to ensure they are within the valid range of 0 to 1.
 * If any color component exceeds 1, all color components are divided by the maximum value to normalize the color.
 * 
 * @param colorValue The color value to be normalized
 * 
 * @return The normalized color value
 */
t_color normalizeColor(t_color colorValue) {
    float max_val = fmax(colorValue.r, fmax(colorValue.g, colorValue.b));
    if (max_val > 1) {
        colorValue.r = colorValue.r / max_val;
        colorValue.g = colorValue.g / max_val;
        colorValue.b = colorValue.b / max_val;
        return (colorValue);
    }
    return colorValue;
}

/**
 * @brief Creates a camera configuration for rendering the scene
 * 
 * This function creates a camera configuration for rendering the scene based on the specified parameters.
 * 
 * @param hsize The horizontal size of the view plane in pixels
 * @param vsize The vertical size of the view plane in pixels
 * @param field_of_view The field of view angle in radians
 * 
 * @return The camera configuration including the view plane dimensions, pixel size, and transformation matrix
 */
t_camera_fn camera(int hsize, int vsize, float field_of_view)
{
    t_camera_fn c;
    float aspect;
    float hview;

    c.vsize = vsize;
    c.hsize = hsize;
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
    c.transform = _identity(4);
    return (c);
}

/**
 * @brief Creates a ray for a specific pixel on the camera's view plane
 * 
 * This function creates a ray for a specific pixel on the camera's view plane based on the camera configuration.
 * 
 * @param c The camera configuration including the view plane dimensions and transformation matrix
 * @param px The x-coordinate of the pixel on the view plane
 * @param py The y-coordinate of the pixel on the view plane
 * 
 * @return A pointer to the ray for the specified pixel
 */

/*
<<<*********************************-THE OLD VR-*********************************>>>
*/

t_ray *ray_for_pixel(t_camera_fn c, int px, int py)
{
    float world_x;
    float world_y;
    t_tuple pixel;

    world_x = c.hwidth - (px + 0.5) * c.pixel_size;
    world_y = c.hheight - (py + 0.5) * c.pixel_size;
    pixel = mtx_tuple_prod(c.transform, _point(world_x, world_y, -1));
    return (_ray(mtx_tuple_prod(c.transform, _point(0, 0, 0)),
            vec_normalize(subtract_tuples(pixel,
            mtx_tuple_prod(c.transform, _point(0, 0, 0))))));
}

/**
 * @brief Sorts a list of intersection points in ascending order based on the parameter t
 * 
 * This function sorts a list of intersection points in ascending order based on the parameter t.
 * 
 * @param lst A pointer to the list of intersection points to be sorted
 * 
 * @return A pointer to the sorted list of intersection points
 */
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
    return (lst);
}

/**
 * @brief Finds the intersections of a ray with the objects in the world
 * 
 * This function finds the intersections of a given ray with the objects in the world and returns a list of intersection points.
 * 
 * @param w A pointer to the world containing the objects
 * @param r A pointer to the ray for which the intersections are to be found
 * 
 * @return A pointer to the list of intersection points
 */
t_lst_inter *intersect_world(t_world *w, t_ray *r)
{
    t_lst_inter *lst = NULL;
    t_inter **xs = NULL;
    t_obj_lst *obj = w->obj_lst;
    t_ray *r1;
    while (obj != NULL)
    {
        if (obj->obj->type == PLANE)
            xs = intersect_pl(r, obj->obj);
        else if (obj->obj->type == CYLINDER)
        {
            r1 = transform_ray(r, obj->obj->transform);
            xs = intersect_caps(obj->obj, r1);
            _intersections(&lst, xs);
            xs = local_intersect(obj->obj, r1);
        }
        else if (obj->obj->type == SPHERE)
            xs = intersect_sp(r, obj->obj);
        if (xs)
            _intersections(&lst, xs);
        r1 = NULL;
        obj = obj->next;
    }
    lst = lst_sort(lst);
    return (lst);
}

/**
 * @brief Prepares the intersection information for shading computations
 * 
 * This function prepares the intersection information for shading computations by calculating the intersection point,
 * the eye vector, the normal vector, and other relevant properties based on the intersection and the ray.
 * 
 * @param inter The intersection information including the parameter t and the intersected object
 * @param ray The ray for which the intersection information is being prepared
 * 
 * @return A pointer to the prepared intersection information (comps)
 */
t_comps *prepare_computations(t_inter *inter, t_ray *ray)
{
    t_comps *comps;

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
    {
        comps->normalv = local_normal_at(comps->obj, comps->point);
    }
    if (dot_product(comps->normalv, comps->eyev) < EPSILON)
    {
        comps->inside = 1;
        if (comps->obj->type == PLANE)
            comps->normalv = multiply_tuple_scalar(-1, comps->obj->pl->vec);
        else 
            comps->normalv = multiply_tuple_scalar(-1, comps->normalv);
    }
    else
        comps->inside = 0;
    comps->over_point = add_tuples(comps->point, multiply_tuple_scalar(EPSILON, comps->normalv));
    return (comps);
}

/**
 * @brief Calculates the color at a given intersection point using ray tracing
 * 
 * This function calculates the color at a given intersection point using ray tracing by finding the intersection
 * of the ray with the objects in the world, preparing the intersection information, and shading the intersection point.
 * 
 * @param w A pointer to the world containing the objects and the light source
 * @param r A pointer to the ray for which the color is to be calculated
 * 
 * @return The color at the intersection point
 */
t_color color_at(t_world *w, t_ray *r)
{
    t_lst_inter *lst;
    t_inter *h;

    lst = intersect_world(w, r);
    h = hit(lst);
    if (h == NULL)
        return (_color(0, 0, 0));
    t_color color = shade_hit(w, prepare_computations(h, r));
    return (color);
}

/**
 * @brief Calculates the shaded color at a given intersection point
 * 
 * This function calculates the shaded color at a given intersection point based on the lighting conditions and object properties.
 * 
 * @param world A pointer to the world containing the objects and the light source
 * @param copms A pointer to the intersection information and properties
 * 
 * @return The shaded color at the intersection point
 */
t_color shade_hit(t_world *world, t_comps *copms)
{
    int shadowed;
    shadowed = is_shadowed(world, copms->point);
    return(illuminate(copms->obj, copms->point, world->light, copms->eyev, shadowed));
}

/**
 * @brief Renders the scene using ray tracing
 * 
 * This function renders the scene using ray tracing by calculating the color of each pixel in the image.
 * 
 * @param c The camera configuration for rendering the scene
 * @param w A pointer to the world containing the objects and the light source
 * @param image A pointer to the image where the rendered scene will be stored
 */
void render(t_camera_fn c, t_world *w, mlx_image_t **image)
{	
    t_ray *r = NULL;
    t_color color;
    int32_t color_int;
    int y = 0;
    int x = 0;

    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            r = ray_for_pixel(c, x, y);
            color = color_at(w, r);
            color = normalizeColor(color);
            if (w->light.brightness != 0)
                color = multiply_color_scalar(w->light.brightness, color);
            color = _color255(color);
            color_int = ft_pixel((int)(color.r), (int)(color.g), \
                                        (int)(color.b));
            mlx_put_pixel((*image), x, y, color_int);
            x++;
        }
        y++;
    }
}

/**
 * @brief Creates a view transformation matrix for a camera
 * 
 * This function creates a view transformation matrix for a camera based on the specified parameters.
 * 
 * @param from The point representing the camera's position in the world
 * @param to The point representing the position the camera is looking at
 * @param up The vector representing the upward direction of the camera
 * 
 * @return A pointer to the view transformation matrix
 */
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

/**
 * @brief Frees the memory allocated for a 2D array of floats
 * 
 * This function frees the memory allocated for a 2D array of floats.
 * 
 * @param mtx The 2D array of floats to be freed
 * @param size The size of the 2D array
 */
void	free_f_mtx(float **mtx, int size)
{
    while (size)
    {
        free(mtx[size - 1]);
        size--;
    }
    free(mtx);
}

/**
 * @brief Checks if a point is shadowed by any object in the world from the light source
 * 
 * This function checks if a given point in the world is shadowed by any object in the world from the light source.
 * 
 * @param w A pointer to the world containing the objects and the light source
 * @param p The point in the world to be checked for shadows
 * 
 * @return 1 if the point is shadowed, 0 otherwise
 */
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
    if (h != NULL && h->t < distance)
    {
        free(r);
        return (1);
    }
    free(r);
    return (0);
}

int main ()
{
    // Create objects in the scene
    t_object *floor = _plane(_point(0, 0, 0), _vector(0, 1, 0), _color(1, 1, 1));

    t_object *middle = _cylinder(_point(0, 0, 0), _vector(0, 0, 0), 1, 2, 0, _color(1, 0, 0));
    middle->specs.diffuse = 0.7;
    middle->specs.specular = 0;
    middle->transform = inverse(translation(0, 1, 5));
    set_transform(&middle, rotation_x(M_PI_4));

    t_object *right = _sphere(_point(0, 0, 0), 1, _color(0.5, 1, 0.1));
    right->specs.diffuse = 0.7;
    right->specs.specular = 0;
    right->transform = inverse(translation(3, 1, 3));

    t_object *left = _sphere(_point(0, 0, 0), 1, _color(0.5, 1, 0.1));
    left->specs.diffuse = 0.7;
    left->specs.specular = 0;
    left->transform = inverse(mtx_multiply(translation(-2, 1, 2), scaling_mtx(1, 1, 1)));

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
    c.transform = inverse(c.transform);
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
