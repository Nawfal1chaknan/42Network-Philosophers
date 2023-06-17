NAME = philo

CFLAGS = -Wall -Wextra -Werror# -fsanitize=thread -g

FILES = philosophers.c utils.c utils2.c actions.c pthread_and_mutex.c check_errors.c

all : $(NAME)

$(NAME) : $(FILES)
		@$(CC) $(CFLAGS) $(FILES) -o $(NAME)

clean :
		@$(RM) $(NAME)

fclean : clean

re : fclean all