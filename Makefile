NAME			=	minishell

SRCS 			=	main.c build_in.c signal.c parsing.c utils.c env.c

OBJS			=	${addprefix srcs/,${SRCS:.c=.o}}

CFLAGS			=	-Wall -Werror -Wextra -Iincludes -Iprintf/include -Iprintf/libft

CC				=	gcc

HEADER			=	includes/minishell.h

PRINTF			= 	@printf "Generate Printf\n" && cd ./printf && make

LIBFT			= 	@printf "Generate Libft\n" && cd ./printf/libft && make

all				:	${NAME}

${NAME}			:	${OBJS} ${HEADER}
					${LIBFT}
					${PRINTF}
					${CC} ${CFLAGS} ${OBJS} -lreadline -g ./printf/libftprintf.a ./printf/libft/libft.a -o ${NAME}

clean			:
					@rm -f ${OBJS}
					@cd ./printf && make clean
					@cd ./printf/libft && make clean

fclean			:
					@rm -f ${OBJS}
					@rm -f ${NAME}
					@cd ./printf && make fclean
					@cd ./printf/libft && make fclean

re				:	fclean all

.PHONY			:	all clean fclean re bonus