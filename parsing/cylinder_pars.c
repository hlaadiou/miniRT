/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_pars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:46:18 by azgaoua           #+#    #+#             */
/*   Updated: 2024/03/16 23:06:19 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pars.h"

void	cylinder_pars(char *line, t_pars **pars)
{
	t_pars	*new;
	char	**tab;

	tab = str_split(line, " \t\r\f\n\v");
	if (ft_tab_size(tab) != 6)
	{
		ft_putstr_fd("Error: wrong number of specific informations\n", 2);
		exit(0);
	}
	new = ft_lstnew(tab[0], tab, 6);
	ft_lstadd_back(pars, new);
}
