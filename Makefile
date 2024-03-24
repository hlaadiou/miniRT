# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/10 20:19:42 by azgaoua           #+#    #+#              #
#    Updated: 2024/03/24 01:13:21 by hlaadiou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT


libobj = 	./libft/get_next_line_utils.o	\
			./libft/get_next_line.o		\
			./libft/ft_strdup.o			\
			./libft/ft_substr.o 		\
			./libft/ft_split.o			\
			./libft/ft_memset.o			\
			./libft/ft_bzero.o			\
			./libft/ft_memcpy.o			\
			./libft/ft_memmove.o 		\
			./libft/ft_memchr.o			\
			./libft/ft_memcmp.o			\
			./libft/ft_strlen.o			\
			./libft/ft_isalpha.o 		\
			./libft/ft_isdigit.o		\
			./libft/ft_isalnum.o		\
			./libft/ft_isascii.o		\
			./libft/ft_isprint.o		\
			./libft/ft_toupper.o		\
			./libft/ft_tolower.o		\
			./libft/ft_strchr.o			\
			./libft/ft_strrchr.o		\
			./libft/ft_strncmp.o		\
			./libft/ft_strlcpy.o		\
			./libft/ft_strlcat.o		\
			./libft/ft_strnstr.o		\
			./libft/ft_atoi.o			\
			./libft/ft_strjoin.o		\
			./libft/ft_strtrim.o		\
			./libft/ft_itoa.o			\
			./libft/ft_strmapi.o		\
			./libft/ft_striteri.o		\
			./libft/ft_putchar_fd.o		\
			./libft/ft_putstr_fd.o		\
			./libft/ft_putendl_fd.o		\
			./libft/ft_putnbr_fd.o		\

FILES = parsing/main.c \
		parsing/ambient_lightning.c \
		parsing/camera.c \
		parsing/light.c \
		parsing/sphere_pars.c \
		parsing/plane_pars.c \
		parsing/cylinder_pars.c \
		parsing/check_elements.c \
		parsing/data_validation.c \
		#parsing/parser.c

OBJS = $(FILES:.c=.o) 

CC = cc

RM = rm -rf

FLGS = -Wall -Wextra -Werror #-fsanitize=address -g3

all :  $(NAME)

%.o: %.c parsing/pars.h ./libft/libft.h 
	@$(CC) $(FLGS) -c $< -o $@

$(NAME) :  $(OBJS) $(libobj)
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
	@$(RM) $(NAME)

re: fclean all
