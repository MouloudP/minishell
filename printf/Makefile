SRC=srcs/ft_printf.c srcs/ft_p.c srcs/ft_printf_utils.c srcs/ft_putnbr_base.c srcs/ft_u.c srcs/ft_x.c
NAME=libftprintf.a
CC=gcc
RM=rm -f
CFLAGS=-Wall -Wextra -Werror
INCLUDES=-Iinclude/
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
		ar rc $(NAME) $(OBJ)
		ranlib $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

clean:
			$(RM) $(OBJ)

fclean: clean
			$(RM) $(NAME)

re: fclean all

.PHONY: fclean clean
