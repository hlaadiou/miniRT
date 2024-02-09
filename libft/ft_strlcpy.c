/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:24:25 by azgaoua           #+#    #+#             */
/*   Updated: 2022/10/24 00:45:20 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h" 

size_t	ft_strlcpy(char *dest, const char *src,
						size_t size)
{
	size_t	i;
	size_t	x;

	x = ft_strlen((char *)(src));
	i = 0;
	if (size != 0)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (x);
}
