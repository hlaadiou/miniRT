# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/10 20:19:42 by azgaoua           #+#    #+#              #
#    Updated: 2024/03/11 15:57:26 by azgaoua          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

OBJS = main.o parsing/ambient_lightning.o

libobj = 	./libft/get_next_line_utils.c	\
			./libft/get_next_line.c		\
			./libft/ft_strdup.c			\
			./libft/ft_substr.c 		\
			./libft/ft_split.c			\
			./libft/ft_memset.c			\
			./libft/ft_bzero.c			\
			./libft/ft_memcpy.c			\
			./libft/ft_memmove.c 		\
			./libft/ft_memchr.c			\
			./libft/ft_memcmp.c			\
			./libft/ft_strlen.c			\
			./libft/ft_isalpha.c 		\
			./libft/ft_isdigit.c		\
			./libft/ft_isalnum.c		\
			./libft/ft_isascii.c		\
			./libft/ft_isprint.c		\
			./libft/ft_toupper.c		\
			./libft/ft_tolower.c		\
			./libft/ft_strchr.c			\
			./libft/ft_strrchr.c		\
			./libft/ft_strncmp.c		\
			./libft/ft_strlcpy.c		\
			./libft/ft_strlcat.c		\
			./libft/ft_strnstr.c		\
			./libft/ft_atoi.c			\
			./libft/ft_strjoin.c		\
			./libft/ft_strtrim.c		\
			./libft/ft_itoa.c			\
			./libft/ft_strmapi.c		\
			./libft/ft_striteri.c		\
			./libft/ft_putchar_fd.c		\
			./libft/ft_putstr_fd.c		\
			./libft/ft_putendl_fd.c		\
			./libft/ft_putnbr_fd.c		\

FILES = main.c parsing/ambient_lightning.c

CC = cc

RM = rm -rf

FLGS = -Wall -Wextra -Werror -fsanitize=address -g3

all :  $(NAME)

%.o: %.c pars.h ./libft/libft.h $(libobj)
	@$(CC) $(FLGS) -c $< -o $@

$(NAME) :  $(OBJS)
	@echo "------>making the miniRT<------"
	@make -C ./libft
	@$(CC) $(FLGS) $(OBJS) libft/libft.a -o $(NAME)
	@echo "--------->miniRT Done<---------"

clean:
	@echo " clean all this FILES if exist: $(OBJS)"
	@make clean -C ./libft
	@$(RM) $(OBJS)

fclean:  clean
	@echo "		+ that --> $(NAME) libft/libft.a"
	@make fclean -C ./libft
	@$(RM) $(NAME) libft/libft.a

re: fclean all