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

NAME = miniRT
CC = cc 
CFLAGS = -Wall -Wextra -Werror
SRCS = srcs/main.c
OBJS = $(SRCS:.c=.o)
LIBFT = libft/libft.a
INC = miniRT.h

all: $(NAME)

$(NAME) : $(OBJS) $(INC)
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LIBFT)

re: fclean all

.PHONY: all clean fclean re