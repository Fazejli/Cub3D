# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/21 18:33:48 by fadzejli          #+#    #+#              #
#    Updated: 2026/02/17 15:53:39 by mattcarniel      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D
CC			= clang 
CFLAGS		= -Wall -Wextra -Werror -MMD -MP -g

SRC_DIR		= src
OBJ_DIR		= .obj
INC_DIR		= include

SRC_FILES	= main.c \
	utils/errors.c \
	parsing/parsing_cleanup.c \
	parsing/parse_data.c \
	parsing/parse_textures.c \
	parsing/parse_colors.c \
	parsing/parse_map.c \
	parsing/valid_map.c \
	parsing/valid_map_utils.c \
	parsing/parse_utils.c \
	raycasting/init_game.c \
	raycasting/raycasting.c \
	raycasting/raycasting_utils.c \
	raycasting/printing.c \
	raycasting/print_textures.c \
	raycasting/cleanup.c

SRC			= $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ			= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEP			:= $(OBJ:.o=.d)

LIBFT = libft/libft.a

UNAME		:= $(shell uname)
ifeq ($(UNAME), Linux)
	MLX_DIR		= mlx_linux
	MLX_LIB		= $(MLX_DIR)/libmlx.a
	MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
else ifeq ($(UNAME), Darwin)
	MLX_DIR		= mlx_opengl
	MLX_LIB		= $(MLX_DIR)/libmlx.a
	MLX_FLAGS	= -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else
	$(error "Unsupported OS: $(UNAME)")
endif

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $< -> $@"
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(MLX_DIR) -c $< -o $@ -MMD

$(LIBFT):
	@echo "Compiling Libft..."
	@$(MAKE) -s -C libft

$(MLX_LIB):
	@echo "Compiling mlx_lib..."
	@$(MAKE) -s -C $(MLX_DIR)

$(NAME) : $(LIBFT) $(MLX_LIB) $(OBJ)
	@echo "Compiling Cub3D..."
	@$(CC) $(CFLAGS) $(OBJ) ${LIBFT} $(MLX_FLAGS) -o $@ 
	
clean:
	@echo "Cleaning objects..."
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -s -C libft
	@$(MAKE) clean -s -C $(MLX_DIR)
	@echo "Objects cleaned!"

fclean: clean
	@echo "Cleaning all..."
	@rm -rf $(NAME)
	@rm -rf ${LIBFT}
	@rm -rf ${MLX_LIB}
	@echo "All cleaned!"

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re