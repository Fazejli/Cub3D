# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/21 18:33:48 by fadzejli          #+#    #+#              #
#    Updated: 2026/02/12 12:13:07 by fadzejli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc 
CFLAGS = -Wall -Wextra -Werror -g
SRCS = srcs/main.c \
	srcs/utils/errors.c \
	srcs/utils/cleanup.c \
	srcs/parsing/parse_data.c \
	srcs/parsing/parse_textures.c \
	srcs/parsing/parse_colors.c \
	srcs/parsing/parse_map.c \
	srcs/parsing/valid_map.c \
	srcs/parsing/parse_utils.c \
	srcs/debug/parsing_debug.c
OBJS = $(SRCS:.c=.o)
INC = inc/cub3d.h
LIBFT = libft/libft.a

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

$(NAME) : $(OBJS) $(INC)
	@echo "Compiling Cub3D..."
	make -C libft
	make clean -C libft
	$(CC) $(CFLAGS) $(OBJS) ${LIBFT} -o $@
	
clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)
	rm -rf ${LIBFT}

re: fclean all

.PHONY: all clean fclean re