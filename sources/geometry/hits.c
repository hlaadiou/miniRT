/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hits.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:53:04 by hlaadiou          #+#    #+#             */
/*   Updated: 2024/07/17 00:15:54 by azgaoua          ###   ########.fr       */
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

t_inter **local_intersect(t_object *cy, t_ray r) 
{
    t_inter **inter = ft_malloc(sizeof(t_inter *) * 2);
    if (inter == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    float a = (r.dir.x * r.dir.x) + (r.dir.z * r.dir.z);
    if (fabs(a) < 0 || fabs(r.dir.y) < 0) 
        return (NULL);
    float b = 2 * ((r.dir.x * r.org.x) + (r.dir.z * r.org.z));
    float c = (r.org.x * r.org.x) + (r.org.z * r.org.z) - (powf(cy->cy->diameter, 2) / 4.0f);
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return (NULL);
    float sqrt_discriminant = sqrt(discriminant);
    float t1 = (-b - sqrt_discriminant) / (2 * a);
    float t2 = (-b + sqrt_discriminant) / (2 * a);
    if (t1 < 0 && t2 < 0)
        return (NULL);
    inter[0] = ft_malloc(sizeof(t_inter));
    inter[1] = ft_malloc(sizeof(t_inter));
    if (inter[0] == NULL || inter[1] == NULL)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    if (t1 > t2)
    {
        float tmp = t1;
        t1 = t2;
        t2 = tmp;
    }
    float y0 = r.org.y + t1 * r.dir.y;
    if (cy->cy->min < y0 && y0 < cy->cy->max)
    {
        inter[0]->t = t1;
        inter[0]->obj = cy;
    }
    float y1 = r.org.y + t2 * r.dir.y;
    if (cy->cy->min < y1 && y1 < cy->cy->max)
    {
        inter[1]->t = t2;
        inter[1]->obj = cy;
    }
    return (inter);
}
