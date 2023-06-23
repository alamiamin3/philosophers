NAME = philo

SRC = philo.c  philo_utils.c philo_utils2.c philo_utils3.c ./utils/ft_atoi.c ./utils/ft_strlen.c ./utils/ft_isdigit.c
CC = gcc 
CFLAGS = -Wall -Werror -Wextra
OBJS = ${SRC:%.c=%.o}

all: ${NAME}
%.o: %.c philo.h
	 ${CC} ${CFLAGS} -c $< -o ${<:%.c=%.o}
$(NAME): ${OBJS} 
	${CC} ${CFLAGS} ${OBJS} -o philo
clean:
		rm -rf  ${OBJS} 

fclean:	clean
		rm -rf ${NAME} 
		
re:		fclean all