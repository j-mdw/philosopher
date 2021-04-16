#ifndef PHILO_ONE_H
# define PHILO_ONE_H

typedef enum	e_print_msg {
	fork,
	eat,
	sleep,
	think, 
	dead
}				t_print_msg;

typedef struct	philo_state {
	int last_meal;
	int isdead;
}				philo_state_t;

typedef struct	philo_shared_data_s {
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
	pthread_mutex_t	*mutex_arr;
	philo_state_t	*philo_state;

}				philo_shared_data_t;

#endif
