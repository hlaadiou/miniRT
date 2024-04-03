/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hits.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:53:04 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/04/03 10:30:05 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/* RETURNS THE LOWEST NONNEGATIVE INTERSECTION
** !! WARNING !! WE ASSUME THAT THE HIT WILL BE 'IF ANY' IN THE BEGINNING OF THE LIST
** THIS COULD NOT BE THE CASE! */
t_inter	*hit(t_lst_inter *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (lst->inter && lst->inter->t >= EPSILON)
			return (lst->inter);
		lst = lst->next;
	}
	return (NULL);
}
