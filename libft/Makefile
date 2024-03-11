# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azgaoua <azgaoua@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/16 08:06:59 by azgaoua           #+#    #+#              #
#    Updated: 2024/03/11 14:41:02 by azgaoua          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = get_next_line_utils.c	\
		get_next_line.c		\
		ft_strdup.c			\
		ft_substr.c 		\
		ft_split.c			\
		ft_memset.c			\
		ft_bzero.c			\
		ft_memcpy.c			\
		ft_memmove.c 		\
		ft_memchr.c			\
		ft_memcmp.c			\
		ft_strlen.c			\
		ft_isalpha.c 		\
		ft_isdigit.c		\
		ft_isalnum.c		\
		ft_isascii.c		\
		ft_isprint.c		\
		ft_toupper.c		\
		ft_tolower.c		\
		ft_strchr.c			\
		ft_strrchr.c		\
		ft_strncmp.c		\
		ft_strlcpy.c		\
		ft_strlcat.c		\
		ft_strnstr.c		\
		ft_atoi.c			\
		ft_strjoin.c		\
		ft_strtrim.c		\
		ft_itoa.c			\
		ft_strmapi.c		\
		ft_striteri.c		\
		ft_putchar_fd.c		\
		ft_putstr_fd.c		\
		ft_putendl_fd.c		\
		ft_putnbr_fd.c		\

OBJS = $(SRCS:.c=.o) 
OBJ_BNS = $(bns_src:.c=.o)

CC = cc

CC_FLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o : %.c libft.h
	@$(CC) $(CC_FLAGS) -c $<

$(NAME): $(OBJS)
	@echo "-------> making Libft <-------"
	@ar rc $(NAME) $(OBJS)
	@echo "-------> Libft Done <-------"

clean:
	@rm -rf $(OBJS) $(OBJ_BNS)

fclean: clean
	@rm -rf $(NAME)

re : fclean all
