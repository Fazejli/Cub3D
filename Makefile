# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/21 18:33:48 by fadzejli          #+#    #+#              #
#    Updated: 2026/01/23 12:23:01 by fadzejli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc 
CFLAGS = -Wall -Wextra -Werror -g
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
	srcs/debug/parsing_debug.c \
	srcs/game/init_game.c \
	srcs/game/raycasting.c \
	srcs/game/rendering.c \
	srcs/game/events.c \
	srcs/game/movements.c \
	srcs/game/utils.c
OBJS = $(SRCS:.c=.o)
LIBFT = libft/libft.a
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	MLX_DIR = mlx
	MLX_LIB = $(MLX_DIR)/libmlx.a
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
else
	MLX_DIR = mlx_opengl
	MLX_LIB = $(MLX_DIR)/libmlx.a
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif
INC = inc/cub3d.h

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

$(MLX_LIB):
	@echo "Compiling MiniLibX..."
	@make -C $(MLX_DIR) 2>/dev/null || echo "MLX already compiled"

$(NAME) : $(MLX_LIB) $(OBJS) $(INC)
	@echo "Compiling..."
	make -C libft
	make clean -C libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "✓ cub3D compiled successfully!"
	
clean:
	rm -rf $(OBJS)
	@echo "✓ Objects cleansed successfully!"

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LIBFT)
	@echo "✓ cub3D executor cleansed successfully!"

re: fclean all

.PHONY: all clean fclean re%  