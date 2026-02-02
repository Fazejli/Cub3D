# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/21 18:33:48 by fadzejli          #+#    #+#              #
#    Updated: 2026/01/28 14:41:27 by fadwa            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc 
CFLAGS = -Wall -Wextra -Werror -g
MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
SRCS = srcs/main.c \
	srcs/utils/errors.c \
	srcs/utils/gnl.c \
	srcs/utils/cleanup.c \
	srcs/parsing/parse_data.c \
	srcs/parsing/parse_textures.c \
	srcs/parsing/parse_colors.c \
	srcs/parsing/parse_map.c \
	srcs/parsing/valid_map.c \
	srcs/parsing/parse_utils.c \
	srcs/debug/parsing_debug.c
OBJS = $(SRCS:.c=.o)
LIBFT = libft/libft.a
INC = inc/cub3d.h

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

$(MLX_LIB):
	@echo "Compiling MiniLibX..."
	@make -C $(MLX_DIR) 2>/dev/null || echo "MLX already compiled"

$(NAME) : $(MLX_LIB) $(OBJS) $(INC)
	@echo "Compiling Cub3D..."
	make -C libft
	make clean -C libft
	$(CC) $(CFLAGS) $(LIBFT) $(OBJS) $(MLX_DIR) -o $(NAME)
	
clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LIBFT)

re: fclean all

.PHONY: all clean fclean re