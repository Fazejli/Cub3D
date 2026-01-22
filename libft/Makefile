# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/22 14:41:02 by fadzejli          #+#    #+#              #
#    Updated: 2025/04/29 17:56:24 by fadzejli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc -Wall -Wextra -Werror -g
SRCS = ft_isalpha.c \
	ft_strlcat.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_isdigit.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_strmapi.c \
	ft_itoa.c \
	ft_striteri.c \
	ft_split.c \
	ft_atoi.c \
	ft_strtrim.c \
	ft_strnstr.c \
	ft_is_empty.c \
	ft_isspace.c
SRCS_BONUS = ft_lstnew_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstsize_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstiter_bonus.c \
	ft_lstmap_bonus.c
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
INC = libft.h

all : $(NAME)

%.o : %.c $(INC)
	$(CC) -I. -c $< -o $@

$(NAME): $(OBJS) $(INC)
	ar rcs $(NAME) $(OBJS)

bonus: $(OBJS_BONUS) $(INC)
	ar rcs $(NAME) $(OBJS_BONUS)

clean :
	rm -rf $(OBJS)
	rm -rf $(OBJS_BONUS)

fclean : clean
	rm -rf $(NAME)

re : clean fclean all

.PHONY: clean fclean re
