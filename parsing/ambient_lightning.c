/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_lightning.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:25:08 by azgaoua           #+#    #+#             */
/*   Updated: 2024/03/13 12:16:30 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pars.h"

int		ft_tab_size(char	**tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

void	free_tab(char	**tab)
{
	int    i;

    i = 0;
    while (tab[i] != NULL)
    {
        free(tab[i]);
        i++;
    }
	free(tab[i]);
}

void	ft_ambient(char	*line,t_pars **pars)
{
	t_pars	*new;
	char	**tab;

	tab = str_split(line, " \t\r\f\n\v");
	if (ft_tab_size(tab) != 3)
		exit(0);
	new = ft_lstnew(tab[0], tab, 1);
	ft_lstadd_back(pars, new);
	// free_tab(tab);
}
