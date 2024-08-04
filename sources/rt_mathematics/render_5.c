/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 20:43:10 by azgaoua           #+#    #+#             */
/*   Updated: 2024/07/28 12:28:43 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_lst_inter	*lst_sort(t_lst_inter *lst)
{
	t_lst_inter	*tmp;
	t_lst_inter	*tmp2;
	t_inter		*inter;

	tmp = lst;
	tmp2 = lst;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (tmp->inter && tmp2->inter && tmp->inter->t > tmp2->inter->t)
			{
				inter = tmp->inter;
				tmp->inter = tmp2->inter;
				tmp2->inter = inter;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return (lst);
}
