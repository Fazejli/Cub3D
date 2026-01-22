# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/21 18:33:48 by fadzejli          #+#    #+#              #
#    Updated: 2026/01/21 19:13:31 by fadzejli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc 
CFLAGS = -Wall -Wextra -Werror
SRCS = srcs/main.c \
	srcs/utils/errors.c \
	srcs/utils/gnl.c \
	srcs/parsing/parse_data.c \
	srcs/parsing/parse_elements.c
OBJS = $(SRCS:.c=.o)
LIBFT = libft/libft.a
INC = inc/cub3d.h

all: $(NAME)

$(NAME) : $(OBJS) $(INC)
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
	rm -rf $(OBJS)
	make clean -C libft

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LIBFT)

re: fclean all

.PHONY: all clean fclean re