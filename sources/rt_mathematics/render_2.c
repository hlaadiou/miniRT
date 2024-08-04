/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:12:23 by azgaoua           #+#    #+#             */
/*   Updated: 2024/07/28 15:24:32 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_color	normalize_color(t_color color_value)
{
	float	max_val;

	max_val = fmax(color_value.r, fmax(color_value.g, color_value.b));
	if (max_val > 1)
	{
		color_value.r = color_value.r / max_val;
		color_value.g = color_value.g / max_val;
		color_value.b = color_value.b / max_val;
		return (color_value);
	}
	return (color_value);
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
		x = -1;
		while (++x < WIDTH)
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
		}
		ft_render_progress(y);
	}
}

void	ft_up_check(t_point from, t_point to, t_vector *up)
{
	if (compare_f((*up).x, fabs(subtract_tuples(to, from).x)) && \
		compare_f((*up).y, fabs(subtract_tuples(to, from).y)) && \
		compare_f((*up).z, fabs(subtract_tuples(to, from).z)))
	{
		if (subtract_tuples(to, from).y < EPSILON)
			(*up) = _vector(0, 0, 1);
		else
			(*up) = _vector(0, 0, -1);
	}
}

t_matrix	*view_transform(t_point from, t_point to, t_vector up)
{
	t_matrix		*orientation;
	t_matrix		*translation_mtx;
	t_matrix		*res;
	t_vector		left;
	t_vector		forward;

	ft_up_check(from, to, &up);
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
