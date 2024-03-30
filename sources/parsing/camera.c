/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:52:17 by azgaoua           #+#    #+#             */
/*   Updated: 2024/03/30 00:50:16 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pars.h"

int	count_words(char *str, char *seps)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && ft_strchr(seps, str[i]))
			i++;
		while (str[i] && !ft_strchr(seps, str[i]))
			i++;
		while (str[i] && ft_strchr(seps, str[i]))
			i++;
		count++;
	}
	return (count);
}

void	init_int(int *i, int *j, int *len, int val)
{
	*i = val;
	*j = val;
	*len = val;
}

char	**str_split(char *str, char *seps)
{
	int		i;
	int		j;
	int		len;
	char	**tab;

	init_int(&i, &j, &len, 0);
	tab = (char **)malloc(sizeof(char *) * (count_words(str, seps) + 1));
	while (str[i] && j < count_words(str, seps))
	{
		while (str[i] && ft_strchr(seps, str[i]))
			i++;
		len = i;
		while (str[len] && !ft_strchr(seps, str[len]))
			len++;
		len = i;
		while (str[i] && !ft_strchr(seps, str[i]))
			i++;
		tab[j] = ft_substr(str, len, i - len);
		j++;
	}
	return (tab[j] = NULL, tab);
}

void	ft_camera(char *line, t_pars **pars)
{
	char	**tab;

	tab = str_split(line, " \t\r\f\n\v");
	if (ft_tab_size(tab) != 4)
	{
		ft_putstr_fd("Error\nWrong number of specific informations\n", 2);
		exit(1);
	}
	ft_lstadd_back(pars, ft_lstnew(tab[0], tab, 2));
}
