# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/08 16:42:15 by azgaoua           #+#    #+#              #
#    Updated: 2024/02/09 15:55:04 by azgaoua          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

OBJS =  ambient_lightning.o open_tests.o main.o

FILES = ambient_lightning.c open_tests.c main.c

CC = cc

RM = rm -rf

FLGS = -Wall -Wextra -Werror -fsanitize=address -g3

all :  $(NAME)

%.o: %.c minirt.h ./libft/libft.h
	@$(CC) $(FLGS) -c $< -o $@

$(NAME) :  $(OBJS) $(FILES)
	@echo "------>making the miniRT<------"
	@cd libft && make && make clean
	@$(CC) $(FLGS) $(OBJS) libft/libft.a -o $(NAME)
	@echo "--------->miniRT Done<---------"

clean:
	@echo " clean all the *.o FILES"
	@$(RM) $(OBJS)

fclean:  clean
	@echo " clean --> $(NAME)"
	@$(RM) $(NAME) libft/libft.a

re: fclean all