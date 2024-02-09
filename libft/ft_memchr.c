/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:13:23 by azgaoua           #+#    #+#             */
/*   Updated: 2022/10/21 03:50:37 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	h;
	unsigned char	*str;

	i = 0;
	h = (unsigned char )c;
	str = (unsigned char *)s;
	while (i < n)
	{
		if (str[i] == h)
			return ((void *)s + i);
		i++;
	}
	return (0);
}
