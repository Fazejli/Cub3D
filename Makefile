# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/21 18:33:48 by fadzejli          #+#    #+#              #
#    Updated: 2026/02/20 14:27:36 by smamalig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3D

SRC_DIR := src
LIB_DIR := lib
BUILD_DIR := build

CC := cc
# Add -fenable-matrix ?
CFLAGS := -Wall -Wextra -Werror -Wpedantic -MMD -MP -std=gnu2x -D_GNU_SOURCE
CFLAGS_DEBUG := -Og -g3 -Wpacked -Wshadow -Wpadded -Wconversion \
			   -Wmissing-prototypes -Wmissing-declarations \
			   -Wold-style-definition -Winline -Wsign-conversion -Wundef \
			   -Wcast-align -Wcast-qual -Wwrite-strings -Wuninitialized \
			   -Wdouble-promotion -Wfloat-equal -Wvla -Wnull-dereference \
			   -Wformat=2 -Wredundant-decls -Wmissing-field-initializers \
			   -Wswitch-enum -Wswitch-default -Wpointer-arith \
			   -Wbad-function-cast -Wstrict-aliasing=2 -Wreturn-type \
			   -fstack-protector-strong -fno-omit-frame-pointer -ftrapv \
			   -fstrict-flex-arrays=3
# -Wstrict-prototypes causing issues with mlx compilation

CFLAGS_SANITIZE := $(CFLAGS_DEBUG) -fsanitize=address,undefined \
				   -fno-sanitize-recover=all

CFLAGS_RELEASE := -O2 -fPIE -D_FORTIFY_SOURCE=3 -DNDEBUG \
				 -fstack-protector-strong -fstack-clash-protection \
				 -fcf-protection=full -mtune=native -flto -fno-math-errno \
				 -fno-trapping-math -funroll-loops -fmerge-all-constants \
				 -fstrict-aliasing -fstrict-enums

ifeq ($(MODE), release)
	CFLAGS += $(CFLAGS_RELEASE)
else ifeq ($(MODE), debug)
	CFLAGS += $(CFLAGS_DEBUG)
else ifeq ($(MODE), sanitize)
	CFLAGS += $(CFLAGS_SANITIZE)
else
	MODE=default
endif

ROOT_DIR := $(BUILD_DIR)/$(MODE)
OBJ_DIR := $(ROOT_DIR)/obj

SRC_PARSER		:= $(addprefix parser/, parsing_cleanup.c parse_data.c \
					parse_map.c parse_textures.c parse_colors.c valid_map.c \
					valid_map_utils.c parse_utils.c)
SRC_THREADS		:= $(addprefix threads/, init.c deinit.c run.c add.c)
SRC_HOOKS		:= $(addprefix hooks/, init.c mouse.c keys.c)
SRC_UTILS		:= $(addprefix utils/, errors.c)
SRC_RAYCASTING	:= $(addprefix raycasting/, init_game.c raycasting.c cleanup.c \
					raycasting_utils.c printing.c print_textures.c)
SRC_ENGINE		:= $(addprefix engine/, init.c deinit.c)
SRC_RENDERER	:= $(addprefix renderer/, init.c deinit.c frame.c render.c)
SRC_PHYSICS		:= $(addprefix physics/, init.c deinit.c)
SRC_GFX			:= $(addprefix gfx/, init.c deinit.c present.c image.c loop.c)
SRC_WORLD		:= $(addprefix world/, init.c deinit.c)
SRC_OPTIONS		:= $(addprefix options/, init.c)

SRC_FILES		:= $(SRC_PARSER) $(SRC_THREADS) $(SRC_ENGINE) $(SRC_RENDERER) \
					$(SRC_RAYCASTING) $(SRC_HOOKS) $(SRC_UTILS) $(SRC_PHYSICS) \
					$(SRC_GFX) $(SRC_WORLD) $(SRC_OPTIONS) main.c

SRCS := $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
DEPS := $(OBJ:.o=.d)

LIBFT_DIR := $(LIB_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a

LDFLAGS := -L$(LIBFT_DIR) -lft

UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	LIBMLX_DIR	:= $(LIB_DIR)/mlx_linux
	LIBMLX		:= $(LIBMLX_DIR)/libmlx.a
	LDFLAGS		+= -L$(LIBMLX_DIR) -lmlx -lXext -lX11 -lm -lz -fPIE -flto \
				   -Wl,-z,relro \
				   -Wl,-z,now \
				   -Wl,-z,noexecstack \
				   -Wl,-z,separate-code
else ifeq ($(UNAME), Darwin)
	LIBMLX_DIR	:= $(LIB_DIR)/mlx_opengl
	LIBMLX		:= $(LIBMLX_DIR)/libmlx.a
	LDFLAGS		+= -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else
	$(error "Unsupported OS: $(UNAME)")
endif

INCLUDES := -Iinclude -Isrc -I$(LIBFT_DIR) -I$(LIBMLX_DIR)

.PHONY: all
all: $(NAME)
	@$(MAKE) postbuild --no-print-directory


.PHONY: default
default: all


.PHONY: release
release:
	@$(MAKE) MODE=release --no-print-directory


.PHONY: debug
debug:
	@$(MAKE) MODE=debug --no-print-directory


.PHONY: sanitize
sanitize:
	@$(MAKE) MODE=sanitize --no-print-directory


.PHONY: bonus
bonus: release

.PHONY: postbuild
postbuild:
	cp -f $(ROOT_DIR)/$(NAME) $(NAME)


$(NAME): libs
	@$(MAKE) $(ROOT_DIR)/$(NAME) --no-print-directory


$(ROOT_DIR)/$(NAME): $(OBJS)
	@mkdir -p $(dir $@)
	@echo "Compiling Cub3D..."
	@$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $< -> $@"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -MMD


.PHONY: libs
libs:
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory 2>/dev/null
	@$(MAKE) CC=$(CC) -C $(LIBMLX_DIR) --no-print-directory ->/dev/null


.PHONY: norm
norm:
	echo $(SRCS) | xargs -n1 -P1 norminette


.PHONY: tidy
tidy:
	echo $(SRCS) | xargs -n1 -P$(shell nproc) clang-tidy -p .


.PHONY: clean
clean:
	@echo "Cleaning objects..."
	@$(MAKE) clean -C $(LIBFT_DIR) --no-print-directory
	@$(MAKE) clean -C $(LIBMLX_DIR) --no-print-directory
	@rm -rf $(BUILD_DIR)
	@echo "Objects cleaned!"


.PHONY: fclean
fclean: clean
	@echo "Cleaning all..."
	@rm -rf $(NAME)
	@rm -rf $(LIBFT)
	@rm -rf $(LIBMLX)
	@echo "All cleaned!"


.PHONY: re
re: fclean
	@make all --no-print-directory


-include $(DEPS)
