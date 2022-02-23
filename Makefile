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

PRINTF			= 	@printf "Generate Printf\n" && cd ./printf && make --no-print-directory

PIPEX			= 	@printf "Generate Pipex\n" && cd ./pipex && make --no-print-directory
 
LIBFT			= 	@printf "Generate Libft\n" && cd ./printf/libft && make --no-print-directory

# COLORS
NONE			= \033[0m
CL_LINE			= \033[2K
B_RED			= \033[1;31m
B_GREEN			= \033[1;32m
B_MAGENTA 		= \033[1;35m
B_CYAN 			= \033[1;36m

all				:	${NAME}

${NAME}			:	${OBJS} ${HEADER}
					${LIBFT}
					${PIPEX}
					${PRINTF}
					@${CC} ${CFLAGS} ${OBJS} -lreadline -g ./printf/libftprintf.a ./printf/libft/libft.a ./pipex/pipex -o ${NAME}
					@printf "${B_GREEN}==>{${NAME}} LINKED SUCCESFULLY<==${NONE}\n"

upd_p			:	
					cd	pipex && make --no-print-directory
					${CC} ${CFLAGS} ${OBJS} -lreadline -g ./printf/libftprintf.a ./printf/libft/libft.a ./pipex/pipex -o ${NAME}

clean			:
					@rm -f ${OBJS}
					@cd ./printf && make --no-print-directory clean
					@cd ./pipex && make --no-print-directory clean
					@cd ./printf/libft && make --no-print-directory clean

fclean			:
					@rm -f ${OBJS}
					@rm -f ${NAME}
					@cd ./printf && make --no-print-directory fclean
					@cd ./pipex && make --no-print-directory fclean
					@cd ./printf/libft && make --no-print-directory fclean

re				:	fclean all

.PHONY			:	all clean fclean re