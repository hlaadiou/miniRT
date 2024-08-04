/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 21:36:00 by azgaoua           #+#    #+#             */
/*   Updated: 2024/07/27 16:16:54 by azgaoua          ###   ########.fr       */
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
	new->ptr = lst;
	new->next = NULL;
	return (new);
}

void	ft_free_collector(t_collector **lst)
{
	t_collector		*tmp;
	t_collector		*current;
	t_collector		*next_loop;
	int				i;

	i = 0;
	current = *lst;
	next_loop = NULL;
	if (!lst || !*lst)
		return ;
	while (current)
	{
		ft_declare_freeing(i);
		tmp = current;
		current = current->next;
		if (tmp && tmp->ptr)
		{
			next_loop = tmp->next;
			free(tmp->ptr);
			free(tmp);
		}
		i++;
	}
	printf("\nFreeing is Done!!\n");
	*lst = NULL;
}

void	ft_lst_add_front_clctr(t_collector **lst, t_collector *new)
{
	if (!lst || !new)
		return ;
	new -> next = *lst;
	*lst = new;
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_free_collector(ft_collector());
		put_error("Unexpected malloc fail\n");
	}
	ft_lst_add_front_clctr(ft_collector(), ft_lstnew_clctr(ptr));
	return (ptr);
}
