CC      = cc
NAME    = philo
CFLAGS  = -Wall -Wextra -Werror
SRCS    = philo.c check_input.c utils.c philo_helps.c \
          philo_init.c philo.monitor.c philo_routine.c clean.c \
		  help.c 
OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
