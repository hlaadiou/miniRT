/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 12:18:14 by azgaoua           #+#    #+#             */
/*   Updated: 2024/07/29 12:08:02 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(const char *s, int fd)
{
	unsigned int	j;

	if (!s)
		return ;
	j = 0;
	while (s[j])
	{
		ft_putchar_fd(s[j], fd);
		j++;
	}
}
