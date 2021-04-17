#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

typedef enum	e_print_msg {
	philo_fork,
	philo_eat,
	philo_sleep,
	philo_think, 
	philo_dead
}				t_print_msg;

typedef struct	s_philo_state {
	int last_meal;
	int isdead;
}				t_philo_state;

typedef struct	s_philo_shared_data {
	int				start_time;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
	pthread_mutex_t	*mutex_arr;
	pthread_mutex_t print_mutex;
	struct timeval  timeval_s;
	t_philo_state	*philo_state;
}				t_philo_shared_data;

int		    print_msg(pthread_mutex_t *print_mutex, int state, int id, int time);

#endif
