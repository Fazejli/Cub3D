# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/21 18:33:48 by fadzejli          #+#    #+#              #
#    Updated: 2026/02/18 11:45:59 by mattcarniel      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -Wpedantic -MMD -MP -std=gnu2x -D_GNU_SOURCE
CFLAGS_DEBUG = -Og -g3 -Wpacked -Wstrict-prototypes -Wshadow -Wpadded \
			   -Wconversion -Wmissing-prototypes -Wmissing-declarations \
			   -Wold-style-definition -Winline -Wsign-conversion -Wundef \
			   -Wcast-align -Wcast-qual -Wwrite-strings -Wuninitialized \
			   -Wdouble-promotion -Wfloat-equal -Wvla -Wnull-dereference \
			   -Wformat=2 -Wredundant-decls -Wmissing-field-initializers \
			   -Wswitch-enum -Wswitch-default -Wpointer-arith \
			   -Wbad-function-cast -Wstrict-aliasing=2 -Wreturn-type \
			   -fstack-protector-strong -fno-omit-frame-pointer -ftrapv

CFLAGS_ASAN    = $(CFLAGS_DEBUG) -fsanitize=address,undefined -fno-sanitize-recover=all

CFLAGS_RELEASE = -O2 -fPIE -D_FORTIFY_SOURCE=3 \
				 -fstack-protector-strong -fstack-clash-protection \
				 -fcf-protection=full -mtune=native -flto -fno-math-errno \
				 -fno-trapping-math

# todo: add actual compilation rules
CFLAGS += $(CFLAGS_ASAN)

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
	raycasting/cleanup.c \
	threads/run.c \
	threads/init.c \
	threads/destroy.c \
	threads/add.c

SRC			= $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ			= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEP			:= $(OBJ:.o=.d)

LIBFT = lib/libft/libft.a

UNAME		:= $(shell uname)
ifeq ($(UNAME), Linux)
	MLX_DIR		= lib/mlx_linux
	MLX_LIB		= $(MLX_DIR)/libmlx.a
	MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
	LDFLAGS		+= -pie -flto \
				  -Wl,-z,relro \
				  -Wl,-z,now \
				  -Wl,-z,noexecstack \
				  -Wl,-z,separate-code
else ifeq ($(UNAME), Darwin)
	MLX_DIR		= lib/mlx_opengl
	MLX_LIB		= $(MLX_DIR)/libmlx.a
	MLX_FLAGS	= -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else
	$(error "Unsupported OS: $(UNAME)")
endif

.PHONY: all
all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $< -> $@"
	@$(CC) $(CFLAGS) -I$(INC_DIR) -Ilib/libft/ -I$(MLX_DIR) -c $< -o $@ -MMD

$(LIBFT):
	@echo "Compiling Libft..."
	@$(MAKE) -s -C lib/libft

$(MLX_LIB):
	@echo "Compiling mlx_lib..."
	@$(MAKE) -s CC=$(CC) -C $(MLX_DIR)

$(NAME) : $(LIBFT) $(MLX_LIB) $(OBJ)
	@echo "Compiling Cub3D..."
	@$(CC) $(CFLAGS) $(OBJ) ${LIBFT} $(MLX_FLAGS) $(LDFLAGS) -o $@
	
.PHONY: clean
clean:
	@echo "Cleaning objects..."
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -s -C lib/libft
	@$(MAKE) clean -s -C $(MLX_DIR)
	@echo "Objects cleaned!"

.PHONY: fclean
fclean: clean
	@echo "Cleaning all..."
	@rm -rf $(NAME)
	@rm -rf ${LIBFT}
	@rm -rf ${MLX_LIB}
	@echo "All cleaned!"

.PHONY: re
re: fclean all

-include $(DEP)
