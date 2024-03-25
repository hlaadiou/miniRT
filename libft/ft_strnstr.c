/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:52:40 by azgaoua           #+#    #+#             */
/*   Updated: 2024/03/11 16:01:27 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if ((haystack == 0 && len == 0) || needle[0] == '\0')
		return ((char *) haystack);
	while (haystack[i] != '\0' && i < len)
	{
		while (haystack[i + j] == needle[j] && haystack[i + j] != '\0'
			&& i + j < len)
			j++;
		if (needle[j] == '\0')
			return ((char *) haystack + i);
		i++;
		j = 0;
	}
	return (0);
}
