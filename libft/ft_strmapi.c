/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:57:35 by azgaoua           #+#    #+#             */
/*   Updated: 2022/11/17 16:13:44 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char				*str;
	unsigned int		j;

	if (!s || !f)
		return (0);
	j = ft_strlen(s) + 1;
	str = malloc(j);
	if (!str)
		return (NULL);
	j = 0;
	while (j < ft_strlen(s))
	{
		str[j] = (*f)(j, (char)s[j]);
		j++;
	}
	str[j] = '\0';
	return (str);
}
