/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:34:58 by azgaoua           #+#    #+#             */
/*   Updated: 2024/02/09 11:09:20 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*p;

	if (!s)
		return ((void *)0);
	if (start >= ft_strlen(s))
		return (ft_strdup("\0"));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	p = malloc(len + 1);
	if (!p)
		return (0);
	i = 0;
	while (i < len)
		p[i++] = s[start++];
	p[i] = '\0';
	return (p);
}
