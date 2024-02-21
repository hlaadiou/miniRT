/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hits.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:53:04 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/02/21 17:40:54 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/geometry.h"

/* RETURNS THE LOWEST NONNEGATIVE INTERSECTION
** !! WARNING !! WE ASSUME THAT THE HIT WILL BE 'IF ANY' IN THE BEGINNING OF THE LIST
** THIS COULD NOT BE THE CASE! */
t_inter	*hit(t_lst_inter *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (lst->inter && lst->inter->t >= 0)
			return (lst->inter);
		lst = lst->next;
	}
	return (NULL);
}
