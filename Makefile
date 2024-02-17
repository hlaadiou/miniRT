# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/10 16:30:07 by hlaadiou          #+#    #+#              #
#    Updated: 2024/02/12 15:36:22 by azgaoua          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	miniRT
#SRCS		=	$(shell find ./sources -iname "*.c")
SRCS		=	my_main.c
OBJS		=	$(SRCS:.c=.o)
LIBMLX		=	./lib/MLX42
LIBS		=	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
CFLAGS		=	-Wall -Werror -Wextra -Ofast
CC			=	cc
RM			=	rm -rf


all:		libmlx $(NAME)

libmlx:
			@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o:		%.c
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			$(CC) $(OBJS) $(LIBS) -o $(NAME)

clean:
			$(RM) $(OBJS)
			$(RM) $(LIBMLX)/build

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re libmlx
