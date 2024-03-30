/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colictor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 21:36:00 by azgaoua           #+#    #+#             */
/*   Updated: 2024/03/29 21:41:19 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pars.h"

t_collector	**ft_collector(void)
{
	static t_collector	*colctr;

	return (&colctr);
}

t_collector	*ft_lstnew_clctr(void *lst)
{
	t_collector	*new;

	new = malloc(sizeof(t_collector));
	if (!new)
		return (0);
	ft_lstadd_back_clctr(ft_collector(), new);
	new->ptr = lst;
	new->next = NULL;
	return (new);
}

void	ft_free_collector(t_collector **lst)
{
	t_collector	*head;
	t_collector	*tmp;

	if (!lst || !*lst)
		return ;
	head = *lst;
	while (*lst)
	{
		tmp = head->next;
		free(head->ptr);
		free(head);
		head = tmp;
	}
}

void	ft_lstadd_back_clctr(t_collector **lst, t_collector *new)
{
	t_collector	*last;

	if (!lst)
		return ;
	last = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
	new->next = NULL;
}

void *ft_malloc(size_t size)
{
    void	*ptr;

    ptr = malloc(size);
    if (!ptr)
        exit(1);
    ft_lstadd_back_clctr(ft_collector(), ft_lstnew_clctr(ptr));
    return (ptr);
}
