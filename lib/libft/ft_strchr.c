/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 05:22:26 by azgaoua           #+#    #+#             */
/*   Updated: 2024/07/29 11:47:44 by hlaadiou         ###   ########.fr       */
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
			return ((char *)(s + i));
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	return (NULL);
}
