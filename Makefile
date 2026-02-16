# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/21 18:33:48 by fadzejli          #+#    #+#              #
#    Updated: 2026/02/16 12:28:10 by fadwa            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = clang 
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g

SRCS_DIR = srcs
OBJ_DIR = obj
DEP_DIR = dep

SRCS = $(SRCS_DIR)/main.c \
	$(SRCS_DIR)/utils/errors.c \
	$(SRCS_DIR)/parsing/parsing_cleanup.c \
	$(SRCS_DIR)/parsing/parse_data.c \
	$(SRCS_DIR)/parsing/parse_textures.c \
	$(SRCS_DIR)/parsing/parse_colors.c \
	$(SRCS_DIR)/parsing/parse_map.c \
	$(SRCS_DIR)/parsing/valid_map.c \
	$(SRCS_DIR)/parsing/valid_map_utils.c \
	$(SRCS_DIR)/parsing/parse_utils.c \
	$(SRCS_DIR)/raycasting/init_game.c \
	$(SRCS_DIR)/raycasting/raycasting.c \
	$(SRCS_DIR)/raycasting/raycasting_utils.c \
	$(SRCS_DIR)/raycasting/printing.c \
	$(SRCS_DIR)/raycasting/print_textures.c \
	$(SRCS_DIR)/raycasting/cleanup.c

OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS = $(SRCS:$(SRCS_DIR)/%.c=$(DEP_DIR)/%.d)
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

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(dir $@)
	mkdir -p $(dir $(DEP_DIR)/$*.d)
	$(CC) $(CFLAGS) -Iinc -I$(MLX_DIR) -c $< -o $@ -MF $(DEP_DIR)/$*.d

$(LIBFT):
	@echo "Compiling Libft..."
	make -C libft

$(NAME) : $(LIBFT) $(OBJS)
	@echo "Compiling Cub3D..."
	$(CC) $(CFLAGS) $(OBJS) ${LIBFT} $(MLX_FLAGS) -o $@ 
	
clean:
	@echo "Cleaning objects..."
	rm -rf $(OBJ_DIR)
	rm -rf $(DEP_DIR)
	@make clean -C libft

fclean: clean
	@echo "Cleaning all..."
	rm -rf $(NAME)
	rm -rf ${LIBFT}

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)