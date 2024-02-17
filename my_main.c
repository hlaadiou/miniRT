/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:34:21 by azgaoua           #+#    #+#             */
/*   Updated: 2024/02/13 16:34:27 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include "lib/MLX42/include/MLX42/MLX42.h"
#include "includes/rt_mathematics.h"

#define WIDTH 1024
#define HEIGHT 1024

static mlx_image_t* image;

void	ft_bresenham(int32_t  cordnt_x, int32_t  cordnt_x0, int32_t  cordnt_y, int  cordnt_y0)
{
	float	e_x;
	float	e_y;
	int		maxi;

	e_x = cordnt_x0 - cordnt_x;
	e_y = cordnt_y0 - cordnt_y;
	maxi = fmax(fabsf(e_x), fabsf(e_y));
	e_x /= maxi;
	e_y /= maxi;
	while (((int )(cordnt_x - cordnt_x0) || (int )(cordnt_y - cordnt_y0)) \
	&& cordnt_x <= 1920 && cordnt_y <= 1080 && cordnt_x >= 0 && cordnt_y >= 0)
	{
		cordnt_x += e_x;
		cordnt_y += e_y;
		mlx_put_pixel(image, cordnt_x, cordnt_y, 0x00FF00FF);
	}
}
// -----------------------------------------------------------------------------

void ft_draw_plane(int32_t x, int32_t y, int32_t width, int32_t height, uint32_t color)
{
	for (int32_t i = 0; i < width / 2; ++i)
	{
		color += 2;
		color = color % 0x00FFFFFF;
		for (int32_t j = 0; j < height; ++j)
			mlx_put_pixel(image, x + i, y + j, color);
	}
	color =  0x00FF00FF;
	for (int32_t i = width / 2; i < width; ++i)
	{
		color -= 2;
		color = color % 0xFFFFFFFF;
		for (int32_t j = 0; j < height; ++j)
			mlx_put_pixel(image, x + i, y + j, color);
	}
	
}


int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}


void ft_randomize(void* param)
{
	(void)param;
	// for (uint32_t i = 0; i < image->width; ++i)
	// {
	// 	for (uint32_t y = 0; y < 1; ++y)
	// 	{
	// 		// uint32_t color = ft_pixel(0x00FF, 0x00FF, \
	// 		// 						0x00FF, 0x00FF);
	// ft_bresenham(0, 1080, 0, 0 + 100);
	// ft_bresenham(0, 1080, 0, 0 + 200);
	// ft_bresenham(0, 1080, 0, 0 + 300);
	// ft_bresenham(0, 1080, 0, 0 + 400);
	// ft_bresenham(0, 1080, 0, 0 + 500);
	// ft_bresenham(0, 1080, 0, 0 + 600);
	// ft_bresenham(0, 1080, 0, 0 + 700);
	// ft_bresenham(0, 1080, 0, 0 + 800);
	// ft_bresenham(0, 1080, 0, 0 + 900);
	// draw a plane that starts at 0, 0, 0 and ends at 0, 0, -10
	ft_draw_plane(0, 500, 250, 524, 0x00FF00FF);
	// ft_draw_plane(0, 0, -10, 0, 1, 0, 0x00FF00FF);
	// 		// mlx_put_pixel(image, i, y, color);
	// 	}
	// }
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

int32_t main(void)
{
	mlx_t* mlx;

	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, 1024, 1024)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	mlx_loop_hook(mlx, ft_randomize, mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}