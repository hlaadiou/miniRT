# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/10 16:30:07 by hlaadiou          #+#    #+#              #
#    Updated: 2024/07/12 17:04:54 by azgaoua          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= miniRT

libobj 		= lib/libft/get_next_line_utils.o	\
			lib/libft/get_next_line.o		\
			lib/libft/ft_strdup.o			\
			lib/libft/ft_substr.o 		\
			lib/libft/ft_split.o			\
			lib/libft/ft_memset.o			\
			lib/libft/ft_bzero.o			\
			lib/libft/ft_memcpy.o			\
			lib/libft/ft_memmove.o 		\
			lib/libft/ft_memchr.o			\
			lib/libft/ft_memcmp.o			\
			lib/libft/ft_strlen.o			\
			lib/libft/ft_isalpha.o 		\
			lib/libft/ft_isdigit.o		\
			lib/libft/ft_isalnum.o		\
			lib/libft/ft_isascii.o		\
			lib/libft/ft_isprint.o		\
			lib/libft/ft_toupper.o		\
			lib/libft/ft_tolower.o		\
			lib/libft/ft_strchr.o			\
			lib/libft/ft_strrchr.o		\
			lib/libft/ft_strncmp.o		\
			lib/libft/ft_strlcpy.o		\
			lib/libft/ft_strlcat.o		\
			lib/libft/ft_strnstr.o		\
			lib/libft/ft_atoi.o			\
			lib/libft/ft_strjoin.o		\
			lib/libft/ft_strtrim.o		\
			lib/libft/ft_itoa.o			\
			lib/libft/ft_strmapi.o		\
			lib/libft/ft_striteri.o		\
			lib/libft/ft_putchar_fd.o		\
			lib/libft/ft_putstr_fd.o		\
			lib/libft/ft_putendl_fd.o		\
			lib/libft/ft_putnbr_fd.o

SRCS		=	my_main.c \
				sources/parsing/ambient_lightning.c \
				sources/parsing/atof.c \
				sources/parsing/camera.c \
				sources/parsing/check_elements.c \
				sources/parsing/collector.c \
				sources/parsing/cylinder_pars.c \
				sources/parsing/data_getters.c \
				sources/parsing/data_validation.c \
				sources/parsing/light.c \
				sources/parsing/object_list.c \
				sources/parsing/parser.c \
				sources/parsing/plane_pars.c \
				sources/parsing/sphere_pars.c \
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

OBJS 		= 	$(SRCS:.c=.o)
LIBMLX		=	./lib/MLX42
LIBS		=	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" lib/libft/libft.a
CFLAGS		=	-Wall -Werror -Wextra -O3 #-fsanitize=address -g3
CC			=	cc
RM			=	rm -rf

all :		libmlx libft $(NAME)

libmlx:
			@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
			@make -C ./lib/libft

%.o: 		%.c includes/miniRT.h includes/rt_mathematics.h includes/parsing.h includes/geometry.h includes/lighting.h
			@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) :	$(OBJS) $(libobj)
			@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

clean:
			@make clean -C ./lib/libft
			@$(RM) $(OBJS)
			@$(RM) $(LIBMLX)/build

fclean:		clean
			@make fclean -C ./lib/libft
			@$(RM) $(NAME)

re:			fclean all

# .PHONY:		all clean fclean re libmlx

