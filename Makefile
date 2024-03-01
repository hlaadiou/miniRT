# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/10 16:30:07 by hlaadiou          #+#    #+#              #
#    Updated: 2024/03/01 16:15:47 by azgaoua          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	miniRT
#SRCS		=	$(shell find ./sources -iname "*.c")
SRCS		=	my_main.c \
				sources/geometry/cylinder.c \
				sources/geometry/hits.c \
				sources/geometry/lists.c \
				sources/geometry/objects.c \
				sources/geometry/plane.c \
				sources/geometry/rays.c \
				sources/geometry/sphere.c \
				sources/lighting/colors.c \
				sources/lighting/lights.c \
				sources/lighting/phong.c \
				sources/rt_mathematics/math_ops.c \
				sources/rt_mathematics/mtx.c \
				sources/rt_mathematics/points.c \
				sources/rt_mathematics/rotation.c \
				sources/rt_mathematics/scaling.c \
				sources/rt_mathematics/shearing.c \
				sources/rt_mathematics/transformation.c \
				sources/rt_mathematics/translation.c \
				sources/rt_mathematics/tuple_mtx_ops.c \
				sources/rt_mathematics/tuples.c \
				sources/rt_mathematics/vectors.c \
				sources/rt_mathematics/normalize.c \
				sources/rt_mathematics/reflect.c 
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
