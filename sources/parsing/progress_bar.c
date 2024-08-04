/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress_bar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:15:42 by azgaoua           #+#    #+#             */
/*   Updated: 2024/07/27 16:56:27 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	ft_declare_freeing(int i)
{
	if (i % 1000 == 0)
		printf("\rFreeing elements ...");
}

void	ft_render_progress(int y)
{
	if (((float )y / (HEIGHT) * 100) < 20.0f)
		printf("\r[##--------][%.2f%%] Rendering... ", \
				(float )((y * 100) / (HEIGHT)));
	else if (((float )(y) / (HEIGHT) * 100) < 40.0f && \
				((float)((y * 100) / (HEIGHT))) > 20.0f)
		printf("\r[####------][%.2f%%] Rendering... ", \
				(float)((y * 100) / (HEIGHT)));
	else if (((float)(y) / (HEIGHT) * 100) < 60.0f && \
				((float)((y * 100) / (HEIGHT))) > 40.0f)
		printf("\r[######----][%.2f%%] Rendering... ", \
				(float)((y * 100) / (HEIGHT)));
	else if (((float)(y) / (HEIGHT) * 100) < 80.0f && \
				((float)((y * 100) / (HEIGHT))) > 60.0f)
		printf("\r[########--][%.2f%%] Rendering... ", \
				(float)((y * 100) / (HEIGHT)));
	else if (((float)(y) / (HEIGHT) * 100) < 90.0f && \
				((float)((y * 100) / (HEIGHT))) > 80.0f)
		printf("\r[#########-][%.2f%%] Rendering... ", \
				(float)((y * 100) / (HEIGHT)));
	else if (((float)(y) / (HEIGHT) * 100) < 100.0f && \
				((float)((y * 100) / (HEIGHT))) > 90.0f)
		printf("\r[##########][%.2f%%] Rendering... ", \
				(float)((y * 100) / (HEIGHT)));
}
