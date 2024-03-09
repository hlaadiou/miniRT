/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:34:21 by azgaoua           #+#    #+#             */
/*   Updated: 2024/03/08 18:02:48 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/miniRT.h"

# define WIDTH  1000
# define HEIGHT 1000

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
	if (!((*mlx) = mlx_init(WIDTH, HEIGHT, "miniRT", false)))
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

int32_t main(void)
{
	mlx_image_t		*image;
	mlx_t			*mlx;

	if (ft_mlx(&mlx, &image) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	t_ray		*r = NULL;
	t_inter		**xs = NULL;
	t_point 	ray_origin = _point(0, 0, -5);
	t_point 	position = _point(0, 0, 0); 
	float		wall_size = 7;
	t_object 	*shape = _sphere(_point(0, 0, 0), 1, _color(1.0, 0.0, 0.0));
	t_light		light = _light(_point(-10, 10, -10), 1.0, _color(1.0, 1.0, 1.0));
	t_point		point;
	float	 	world_x = 0;
	float	 	world_y = 0;
	float 		half = wall_size / 2;
	int x;
	int y;

	for (y = 0; y < HEIGHT; y++)
	{
		world_y = half - ((float)((float)wall_size/(float )(HEIGHT) * y));
		for (x = 0; x < WIDTH; x++)
		{
			world_x = -half + ((float)((float)wall_size/(float )(WIDTH) * x));
			position = _point(world_x, world_y, 10);
			r = _ray(ray_origin, vec_normalize(subtract_tuples(position, ray_origin)));
			xs = intersect_sp(r, shape);
			if (xs && (xs[0]->t > 0 || xs[1]->t > 0))
			{
				if (xs[0]->t > 0)
					point = _position(r, xs[0]->t);
				else if (xs[1]->t > 0)
					point = _position(r, xs[1]->t);
				t_color c = illuminate(shape, point, light, ray_origin);
				c = normalizeColor(c);
				c = _color255(c);
				int32_t color = ft_pixel((int)(c.r), (int)(c.g), \
										(int)(c.b), 0x00FF);
				mlx_put_pixel(image, x, y, color);
			}
			else
				mlx_put_pixel(image, x, y, 0x000000FF);

			free(r);
			free(xs);
		}
		printf("progress = -----------------> ( %.2f %%) <----------------- \r", \
				(float )((float )(x*y)/((float )HEIGHT * ((float )WIDTH - 1))) * 100);
		fflush(stdout);
	}
	mlx_loop_hook(mlx, ft_hook, mlx);
	system("clear");
	fflush(stdout);
	printf("DONE !!\r");
	fflush(stdout); 
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
