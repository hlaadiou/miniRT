# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlaadiou <hlaadiou@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/10 16:30:07 by hlaadiou          #+#    #+#              #
#    Updated: 2024/02/11 17:05:25 by hlaadiou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	miniRT
SRCS		=	$(shell find ./sources -iname "*.c")
OBJS		=	$(SRCS:.c=.o)
LIBMLX		=	./lib/MLX42
HEADERS		=	-I ./includes -I $(LIBMLX)/include
LIBS		=	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
CFLAGS		=	-Wall -Werror -Wextra -Ofast
CC			=	cc
RM			=	rm -rf


all:		libmlx $(NAME)

libmlx:
			@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o:		%.c
			$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(NAME):	$(OBJS)
			$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
			$(RM) $(OBJS)
			$(RM) $(LIBMLX)/build

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re libmlx
