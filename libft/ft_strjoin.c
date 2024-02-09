/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 21:56:10 by azgaoua           #+#    #+#             */
/*   Updated: 2022/11/16 23:40:27 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	int		i;
	int		len;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s2) + ft_strlen(s1);
	s = malloc(len + 1);
	if (!s)
		return (0);
	i = 0;
	while (s1[i])
		i++;
	ft_memmove(s, s1, i);
	ft_memmove((s + i), s2, ft_strlen(s2));
	s[len] = '\0';
	return (s);
}
