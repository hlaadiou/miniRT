/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 19:59:11 by azgaoua           #+#    #+#             */
/*   Updated: 2024/03/16 23:09:47 by azgaoua          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARS_H
# define PARS_H

# include "libft/libft.h"

# include <libc.h>

typedef struct s_pars
{
	char					*identifier;
	char					**elements;
	int						flag;
	struct s_pars			*next;
}				t_pars;

char	**str_split(char *str, char *seps);
int		ft_tab_size(char	**tab);
void	ft_ambient(char	*line, t_pars **pars);
void	ft_camera(char *line, t_pars **pars);
void	ft_light(char *line, t_pars **pars);
void	ft_lstadd_back(t_pars **lst, t_pars *new);
void	ft_pars_spher(char *line, t_pars **pars);
t_pars	*ft_lstnew(char *content, char **elms, int flag);
void	plane_pars(char *line, t_pars **pars);
void	cylinder_pars(char *line, t_pars **pars);
void	free_tab(char	**tab);
int		ft_lstsize(t_pars *lst);

#endif