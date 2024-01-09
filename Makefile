SRCS	= $(wildcard src/*.c) $(wildcard src/*/*.c) $(wildcard src/*/*/*.c)
OBJS = ${SRCS:.c=.o}

RM = rm -f
CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = minishell

.c.o:
	${CC} ${CFLAGS} -I./libft -I./includes -c $< -o ${<:.c=.o}

all: 	${NAME}

${NAME}:	${OBJS}
		$(MAKE) -C ./libft
		${CC} -o ${NAME} ${OBJS} ./libft/libft.a -lreadline

clean:
		$(MAKE) clean -C ./libft
		${RM} ${OBJS}

fclean:	clean
		$(MAKE) fclean -C ./libft
		${RM} ${NAME}

re: fclean all

.PHONY:	all clean fclean re
