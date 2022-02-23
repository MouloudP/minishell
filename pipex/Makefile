SRC = main.c utils.c ft_split.c \
command.c utils2.c utils3.c iter_pipes.c\
get_next_line_utils.c \
get_next_line.c \
redirection.c \
open_write.c \
error.c \
parse_cmd.c \
wait_pid.c \
../printf/libft/libft.a \

CC = gcc

LIBC = ar -rc

HEADER = pipex.h \
get_next_line.h \

OBJ = $(SRC:%.c=./.build/%.o)

NAME = pipex

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror

# COLORS
NONE			= \033[0m
CL_LINE			= \033[2K
B_RED			= \033[1;31m
B_GREEN			= \033[1;32m
B_MAGENTA 		= \033[1;35m
B_CYAN 			= \033[1;36m

./.build/%.o : %.c
	@$(CC) ${CFLAGS} -I. -o $@ -c $?
	@printf "${B_MAGENTA}Compilling $? ...\n${NONE}"

all :	
	@mkdir -p .build
	@make --no-print-directory ${NAME}

${NAME} : $(OBJ)
	@printf "${B_CYAN}${NAME} is linking ...${NONE}\n"
	${LIBC} ${NAME} ${OBJ}
	@printf "${B_GREEN}==>{${NAME}} LINKED SUCCESFULLY<==${NONE}\n"

clean :
	@${RM} .build
	@printf "${B_RED}Deleting .build folder ...${NONE}\n"

fclean :	clean
	@${RM} ${NAME}
	@printf "${B_RED}Deleting ${NAME} ...${NONE}\n"

re :	fclean all