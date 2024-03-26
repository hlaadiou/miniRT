/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:04:42 by azgaoua           #+#    #+#             */
/*   Updated: 2024/03/11 14:05:14 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*helper;
	int			sub;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	helper = rdwr_and_search(fd, helper);
	sub = ft_strlen_gnl(helper);
	if (sub && helper[sub - 1])
	{
		sub = -1;
		line = ft_calloc_gnl(ft_strlen_gnl(helper) + 1);
		while (helper[++sub] != '\n' && helper[sub] != '\0')
			line[sub] = helper[sub];
		if (ft_strchr_gnl(helper, '\n'))
		{
			helper = ft_substr_gnl(helper, sub + 1, \
						ft_strlen_gnl(helper) - sub - 1);
			return (line[sub] = '\n', line);
		}
		else if (!ft_strchr_gnl(helper, '\n'))
			return (free(helper), helper = NULL, line);
	}
	return (line);
}

char	*rdwr_and_search(int fd, char *helper)
{
	int		nbr_chars;
	char	*tmp;

	nbr_chars = 1;
	while (nbr_chars > 0)
	{
		tmp = ft_calloc_gnl(BUFFER_SIZE + 1);
		if (!tmp)
			return (NULL);
		nbr_chars = read(fd, tmp, BUFFER_SIZE);
		if (nbr_chars == -1)
			return (free(helper), free(tmp), helper = NULL, NULL);
		else if (nbr_chars > 0 && !ft_strchr_gnl(tmp, '\n'))
		{
			helper = ft_free_and_join(helper, tmp);
			free(tmp);
		}
		else if (nbr_chars == 0 || ft_strchr_gnl(tmp, '\n'))
		{
			helper = ft_free_and_join(helper, tmp);
			return (free(tmp), helper);
		}
	}
	return (helper);
}

char	*ft_strchr_gnl(char *s, int c)
{
	int		i;

	i = 0;
	while (0 == 0)
	{
		if (s[i] == (char )c)
			return (s + i);
		if (s[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}

char	*ft_free_and_join(char *helper, char *line)
{
	char	*tmp1;

	tmp1 = ft_strjoin_gnl(helper, line);
	free(helper);
	return (tmp1);
}
