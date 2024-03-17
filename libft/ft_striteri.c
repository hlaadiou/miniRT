/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:20:27 by azgaoua           #+#    #+#             */
/*   Updated: 2024/03/11 16:01:27 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int		j;

	if (!s || !f)
		return ;
	j = 0;
	while (j < ft_strlen(s))
	{
		f(j, &s[j]);
		j++;
	}
}
