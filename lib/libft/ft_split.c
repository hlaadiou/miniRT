/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:22:43 by azgaoua           #+#    #+#             */
/*   Updated: 2024/03/27 01:44:30 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	lignes(const char *s, char c)
{
	size_t	i;
	size_t	l;

	i = 0;
	l = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			i++;
			l++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (l + 1);
}

static char	**freeme(char **s, size_t i)
{
	while (i >= 0 && s[i] != NULL)
	{
		free(s[i]);
		i--;
	}
	free(s);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**sp;

	i = 0;
	if (!s)
		return (NULL);
	sp = malloc(sizeof(char*) * lignes(s, c));
	if (!sp)
		return (0);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		j = 0;
		while (s[j] && s[j] != c)
			j++;
		if (j != 0)
			sp[i++] = ft_substr(s, 0, j);
		if (j != 0 && !sp[i - 1])
			return (freeme(sp, i - 1));
		s += j;
	}
	sp[i] = NULL;
	return (sp);
}

