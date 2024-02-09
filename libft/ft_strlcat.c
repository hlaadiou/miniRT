/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 04:29:49 by azgaoua           #+#    #+#             */
/*   Updated: 2022/11/07 00:10:24 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	res;
	size_t	sized;

	if ((dst == 0 && size == 0) || size == 0)
		return (ft_strlen(src));
	sized = ft_strlen(dst);
	res = 0;
	i = 0;
	if (size > sized + 1)
	{
		while (i < size - (sized + 1) && src[i] != '\0')
		{
			dst[sized + i] = src[i];
			i++;
		}
	}
	if (size < sized)
		res = ft_strlen(src) + size;
	else
		res = sized + ft_strlen(src);
	dst[sized + i] = '\0';
	return (res);
}
