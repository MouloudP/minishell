NAME			=	minishell

SRCS 			=	main.c \
					build_in.c \
					signal.c \
					parsing/ft_check_parsing.c \
					parsing/ft_check_token.c \
					parsing/ft_parsing_utils1.c \
					parsing/ft_parsing_utils2.c \
					parsing/ft_parsing_utils3.c \
					parsing/ft_check_syntax.c \
					parsing/ft_quote_env.c \
					parsing/ft_gerarg.c \
					parsing/ft_parse_env.c \
					parsing/ft_delimiters.c \
					parsing/ft_parse_token.c \
					utils.c \
					env/env.c \
					env/set_env.c \
					env/utils_env.c \
					env/export.c \
					utils2.c \
					utils3.c \
					exit.c \

OBJS			=	${addprefix srcs/,${SRCS:.c=.o}}

CFLAGS			=	-Wall -Werror -Wextra -Iincludes -Iprintf/include -Iprintf/libft

CC				=	gcc

HEADER			=	includes/minishell.h

PRINTF			= 	@printf "Generate Printf\n" && cd ./printf && make

PIPEX			= 	@printf "Generate Pipex\n" && cd ./pipex && make

LIBFT			= 	@printf "Generate Libft\n" && cd ./printf/libft && make

all				:	${NAME}

${NAME}			:	${OBJS} ${HEADER}
					${LIBFT}
					${PIPEX}
					${PRINTF}
					${CC} ${CFLAGS} ${OBJS} -lreadline -g ./printf/libftprintf.a ./printf/libft/libft.a ./pipex/pipex -o ${NAME}

upd_p			:	
					cd	pipex && make
					${CC} ${CFLAGS} ${OBJS} -lreadline -g ./printf/libftprintf.a ./printf/libft/libft.a ./pipex/pipex -o ${NAME}

clean			:
					@rm -f ${OBJS}
					@cd ./printf && make clean
					@cd ./pipex && make clean
					@cd ./printf/libft && make clean

fclean			:
					@rm -f ${OBJS}
					@rm -f ${NAME}
					@cd ./printf && make fclean
					@cd ./pipex && make fclean
					@cd ./printf/libft && make fclean

re				:	fclean all

.PHONY			:	all clean fclean re