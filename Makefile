# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: feljourb <feljourb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/01 21:57:40 by feljourb          #+#    #+#              #
#    Updated: 2025/04/18 06:57:35 by feljourb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc 

CFLAGS = -Wall -Wextra -Werror

SRCS = cub3d.c Gnl/get_next_line_utils.c Gnl/get_next_line.c parsing/extract_config.c parsing/map.c \
		parsing/free.c parsing/parse_colors.c parsing/parse_textures.c parsing/dfs.c parsing/parse_ext_args.c \
		parsing/parsing_config_utils.c parsing/parse_colors_utils.c

LIBFT = libft/libft.a
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	@make -C libft

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
 

clean:
	rm -f $(OBJ)
	@make -C libft clean

fclean: clean
	rm -f $(NAME)
	@make -C libft fclean

re: fclean all

.PHONY: clean re fclean all 