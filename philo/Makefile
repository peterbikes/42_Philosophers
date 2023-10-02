CC = cc
CFLAGS = -g -Wall -Werror -Wextra -pthread -O2
NAME = philo

SRCS = ./srcs/main.c ./srcs/philos_life.c ./srcs/thread_creation.c ./srcs/utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

${NAME}: ${OBJS}
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)
	
fclean: clean
	rm -rf $(NAME)
	
re: fclean all
