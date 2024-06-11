/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:14:10 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/05/17 11:22:45 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

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

int	main(int argc, char *argv[])
{
	mlx_image_t	*image;
	mlx_t		*mlx;

	if (ft_mlx(&mlx, &image) == EXIT_FAILURE)
		return (EXIT_FAILURE);
}
