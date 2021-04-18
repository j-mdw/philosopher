NAME = philo_one

### FILES

PONE_DIR_C = src/

PONE_DIR_O = obj/

PONE_FILES_C = main.c print_msg.c check_input.c chrono.c init_data.c philo_create.c philo_life.c

PONE_FILES_O = $(addprefix $(PONE_DIR_O), $(PONE_FILES_C:c=o))

### GENERAL

H_FILE = philo_one.h

I = -I ./ 

CC = gcc

C_FLAGS = -Wall -Wextra -Werror $I

PTHREAD_LIB = -pthread

RM = rm -f

### RULES

all: $(NAME)

$(NAME): $(PONE_FILES_O)
	$(CC) $(PTHREAD_LIB) $^ -o $@

$(PONE_DIR_O)%.o: $(PONE_DIR_C)%.c $(H_FILE)
	$(CC) $(C_FLAGS) -c $< -o $@

clean:
	$(RM) $(PONE_FILES_O)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
