NAME = philo_three

### FILES

PHILO_DIR_C = src/

PHILO_DIR_O = obj/

PHILO_FILES_C =	main.c print_msg.c check_input.c \
				chrono.c init_data.c philo_create.c \
				philo_life.c clear_shared_data.c monitor.c \
				my_usleep.c ft_strcpy.c terminate_process.c \
				cpy_nbr.c philo_sem_open.c

PHILO_FILES_O = $(addprefix $(PHILO_DIR_O), $(PHILO_FILES_C:c=o))

### GENERAL

H_FILE = philo_three.h

I = -I ./ 

CC = gcc

C_FLAGS = -Wall -Wextra -Werror $I

PTHREAD_LIB = -pthread

RM = rm -f

### RULES

all: $(NAME)

$(NAME): $(PHILO_FILES_O)
	 $(CC) $(PTHREAD_LIB) $^ -o $@

$(PHILO_DIR_O)%.o: $(PHILO_DIR_C)%.c $(H_FILE)
	 $(CC) $(C_FLAGS) -c $< -o $@

clean:
	$(RM) $(PHILO_FILES_O)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
