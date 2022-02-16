# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/23 11:23:57 by ahamdoun          #+#    #+#              #
#    Updated: 2022/02/05 14:05:54 by ahamdoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a
CC=gcc
RM=rm -f
CFLAGS=-Wall -Wextra -Werror
INCLUDES=libft.h
SRC=ft_atoi.c ft_isascii.c ft_itoa.c ft_memmove.c ft_putstr_fd.c ft_strlcat.c ft_toupper.c ft_bzero.c \
    ft_isdigit.c ft_memccpy.c ft_memset.c ft_split.c ft_strlcpy.c ft_strrchr.c ft_calloc.c ft_islower.c \
    ft_memchr.c ft_putchar_fd.c ft_strchr.c ft_strlen.c ft_strtrim.c ft_isalnum.c ft_isprint.c \
    ft_memcmp.c ft_putendl_fd.c ft_strdup.c ft_strmapi.c ft_substr.c ft_isalpha.c ft_isupper.c \
    ft_memcpy.c ft_putnbr_fd.c ft_strjoin.c ft_strncmp.c ft_tolower.c ft_strcpy.c ft_strnstr.c ft_strcmp.c ft_strndup.c
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
		ar rc $(NAME) $(OBJ)
		ranlib $(NAME)

%.o: %.c
		$(CC) -I. -o $@ -c $? $(CFLAGS)

all: $(NAME)

clean:
			$(RM) $(OBJ)

fclean: clean
			$(RM) $(NAME)

re: fclean all

.PHONY: fclean clean
