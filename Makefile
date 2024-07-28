# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/10 16:30:07 by hlaadiou          #+#    #+#              #
#    Updated: 2024/07/28 15:16:27 by azgaoua          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	miniRT

LIBFT_SRCS 	=	lib/libft/get_next_line_utils.c	\
				lib/libft/get_next_line.c		\
				lib/libft/ft_strdup.c			\
				lib/libft/ft_substr.c 		\
				lib/libft/ft_split.c			\
				lib/libft/ft_memset.c			\
				lib/libft/ft_bzero.c			\
				lib/libft/ft_memcpy.c			\
				lib/libft/ft_memmove.c 		\
				lib/libft/ft_memchr.c			\
				lib/libft/ft_memcmp.c			\
				lib/libft/ft_strlen.c			\
				lib/libft/ft_isalpha.c 		\
				lib/libft/ft_isdigit.c		\
				lib/libft/ft_isalnum.c		\
				lib/libft/ft_isascii.c		\
				lib/libft/ft_isprint.c		\
				lib/libft/ft_toupper.c		\
				lib/libft/ft_tolower.c		\
				lib/libft/ft_strchr.c			\
				lib/libft/ft_strrchr.c		\
				lib/libft/ft_strncmp.c		\
				lib/libft/ft_strlcpy.c		\
				lib/libft/ft_strlcat.c		\
				lib/libft/ft_strnstr.c		\
				lib/libft/ft_atoi.c			\
				lib/libft/ft_strjoin.c		\
				lib/libft/ft_strtrim.c		\
				lib/libft/ft_itoa.c			\
				lib/libft/ft_strmapi.c		\
				lib/libft/ft_striteri.c		\
				lib/libft/ft_putchar_fd.c		\
				lib/libft/ft_putstr_fd.c		\
				lib/libft/ft_putendl_fd.c		\
				lib/libft/ft_putnbr_fd.c

SRCS		=	sources/main.c \
				sources/parsing/ambient_lightning.c \
				sources/parsing/atof.c \
				sources/parsing/progress_bar.c \
				sources/parsing/camera.c \
				sources/parsing/check_elements.c \
				sources/parsing/collector.c \
				sources/parsing/cylinder_pars.c \
				sources/parsing/data_getters.c \
				sources/parsing/data_getters_1.c \
				sources/parsing/data_getters_2.c \
				sources/parsing/data_validation.c \
				sources/parsing/data_validation_1.c \
				sources/parsing/light.c \
				sources/parsing/object_list.c \
				sources/parsing/parser.c \
				sources/parsing/parser_1.c \
				sources/parsing/plane_pars.c \
				sources/parsing/sphere_pars.c \
				sources/geometry/cylinder.c \
				sources/geometry/cylinder_1.c \
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
				sources/rt_mathematics/mtx_1.c \
				sources/rt_mathematics/points.c \
				sources/rt_mathematics/render_1.c \
				sources/rt_mathematics/render_2.c \
				sources/rt_mathematics/render_3.c \
				sources/rt_mathematics/render_4.c \
				sources/rt_mathematics/render_5.c \
				sources/rt_mathematics/rotation.c \
				sources/rt_mathematics/scaling.c \
				sources/rt_mathematics/transformation.c \
				sources/rt_mathematics/translation.c \
				sources/rt_mathematics/tuple_mtx_ops.c \
				sources/rt_mathematics/tuples.c \
				sources/rt_mathematics/vectors.c \
				sources/rt_mathematics/normalize.c \
				sources/rt_mathematics/reflect.c

OBJS 		= 	$(SRCS:.c=.o)
LIBFT_OBJS	=	$(LIBFT_SRCS:.c=.o)
LIBMLX		=	./lib/MLX42
LIBS		=	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" lib/libft/libft.a
CFLAGS		=	-Wall -Werror -Wextra
CC			=	cc
RM			=	rm -rf

all :		libmlx libft $(NAME)

libmlx:
			@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
			@make -C ./lib/libft

%.o: 		%.c includes/miniRT.h includes/rt_mathematics.h includes/parsing.h includes/geometry.h includes/lighting.h
			@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) :	$(OBJS) $(LIBFT_OBJS)
			@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

clean:
			@make clean -C ./lib/libft
			@$(RM) $(OBJS)
			@$(RM) $(LIBMLX)/build

fclean:		clean
			@make fclean -C ./lib/libft
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		clean libmlx libft