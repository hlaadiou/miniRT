/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:13:01 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/07/27 18:27:33 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

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
	if (!((*mlx) = mlx_init(w, h, "miniRT", false))) // NORM ERROR !
	{
		puts(mlx_strerror(mlx_errno)); // Not allowed !
		return (EXIT_FAILURE);
	}
	if (!((*image) = mlx_new_image(*mlx, w, h))) // NORM ERROR !
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

// void	vv(void)
// {
// 	system("leaks miniRT");
// }

int	main(int ac, char **av)
{
	mlx_image_t		*image;
	mlx_t			*mlx;
	t_pars			*conf;
	t_scene			*scene;
	t_camera_fn		cam;

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
	printf("\nRendering is done!!\n");
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	ft_free_collector(ft_collector());
	return (0);
}
