# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/21 18:33:48 by fadzejli          #+#    #+#              #
#    Updated: 2026/02/14 16:36:15 by fadwa            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc 
CFLAGS = -Wall -Wextra -Werror -g -MMD -MP
SRCS = srcs/main.c \
	srcs/utils/errors.c \
	srcs/parsing/parsing_cleanup.c \
	srcs/parsing/parse_data.c \
	srcs/parsing/parse_textures.c \
	srcs/parsing/parse_colors.c \
	srcs/parsing/parse_map.c \
	srcs/parsing/valid_map.c \
	srcs/parsing/parse_utils.c \
	srcs/raycasting/init_game.c \
	srcs/raycasting/raycasting_utils.c \
	srcs/debug/parsing_debug.c
OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)
INC = inc/cub3d.h
LIBFT = libft/libft.a

UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	MLX_DIR = mlx_linux
	MLX_LIB = $(MLX_DIR)/libmlx.a
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
else
	MLX_DIR = mlx_opengl
	MLX_LIB = $(MLX_DIR)/libmlx.a
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -Iinc -I$(MLX_DIR) -c $< -o $@

$(NAME) : $(OBJS) $(INC) $(MLX)
	@echo "Compiling Cub3D..."
	make -C libft
	make clean -C libft
	$(CC) $(CFLAGS) $(OBJS) ${LIBFT} $(MLX_FLAGS) -o $@
	
clean:
	rm -rf $(OBJS)
	rm -rf $(DEPS)

fclean: clean
	rm -rf $(NAME)
	rm -rf ${LIBFT}

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)