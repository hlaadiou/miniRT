/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 05:22:26 by azgaoua           #+#    #+#             */
/*   Updated: 2024/03/11 16:01:27 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (0 == 0)
	{
		if (s[i] == (char)c)
			return (ft_substr(s, 0, i));
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	return (NULL);
}
