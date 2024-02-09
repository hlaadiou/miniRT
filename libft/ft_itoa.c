/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 23:14:46 by azgaoua           #+#    #+#             */
/*   Updated: 2022/11/12 13:57:10 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	*f_rev(char *str)
{
	size_t		ln;
	size_t		i;
	char		c;

	if (!str)
		return (0);
	ln = ft_strlen(str) - 1;
	i = 0;
	if (str[0] == '-')
		i = 1;
	c = 0;
	while (i < ln)
	{
		c = str[i];
		str[i] = str[ln];
		str[ln] = c;
		i++;
		ln--;
	}
	return (str);
}

static char	*ft_finish(char *s, int l, long t)
{
	s[l++] = t + 48;
	s[l++] = '\0';
	f_rev(s);
	return (s);
}

static unsigned int	talloc(long r)
{
	long	k;

	if (r < 0)
	{
		r *= -1;
		k = 2;
	}
	else
		k = 1;
	while (r > 9)
	{
		r /= 10;
		k++;
	}
	return (k + 1);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		j;
	long	i;

	j = 0;
	i = talloc(n);
	s = malloc(i);
	if (!s)
		return (0);
	i = n;
	if (i < 0)
	{
		i *= -1;
		s[0] = '-';
		j = 1;
	}
	while (i >= 10)
	{
		s[j] = (i % 10) + 48;
		i = i / 10;
		j++;
	}
	return (ft_finish(s, j, i));
}
