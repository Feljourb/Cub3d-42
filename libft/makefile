# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/19 18:11:48 by feljourb          #+#    #+#              #
#    Updated: 2023/12/06 21:07:29 by feljourb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc

CFLAGS = -Wall -Wextra -Werror
AR = ar crs
SRCS = ft_isascii.c ft_memset.c ft_strjoin.c ft_strtrim.c ft_isdigit.c ft_putchar_fd.c \
	ft_strlcat.c ft_substr.c ft_isprint.c ft_putendl_fd.c ft_strlcpy.c ft_tolower.c ft_atoi.c \
	ft_itoa.c ft_putnbr_fd.c ft_strlen.c ft_toupper.c ft_bzero.c ft_memchr.c ft_putstr_fd.c  ft_strmapi.c \
	ft_calloc.c ft_memcmp.c ft_strchr.c ft_strncmp.c ft_isalnum.c ft_memcpy.c ft_strdup.c ft_strnstr.c \
	ft_isalpha.c ft_memmove.c ft_striteri.c ft_strrchr.c ft_split.c

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $@ $?

clean:
	rm -f $(OBJ)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean re fclean all