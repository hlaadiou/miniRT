/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_lightning.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:25:08 by azgaoua           #+#    #+#             */
/*   Updated: 2024/07/17 01:04:08 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pars.h"

int	ft_tab_size(char	**tab)
{
	int	i;

	i = 0;
	while (tab && tab[i] != NULL)
		i++;
	return (i);
}

void	free_tab(char	**tab)
{
	int	i;

	i = 0;
	while (tab && tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_ambient(char	*line, t_pars **pars)
{
	char	**tab;

	tab = str_split(line, " \t\r\f\n\v");
	if (ft_tab_size(tab) != 3)
	{
		ft_putstr_fd("Error\nwrong number of specific informations\n", 2);
		// free_tab(tab);
		// ft_free_struct(*pars);
		exit(1);
	}
	ft_lstadd_back(pars, ft_lstnew(tab[0], tab, 1));
	// ft_lst_add_front_clctr(ft_collector(), ft_lstnew_clctr(*pars));
	// ft_lst_add_front_clctr(ft_collector(), ft_lstnew_clctr(tab));
}
