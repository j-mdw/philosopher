#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>

# define FORKS_SEM "forks_sem"
# define FROK_GRAB_SEM "fork_grab"
# define POST_SEM "post_sem"

int g_philo_death;

typedef enum	e_print_msg {
	philo_fork,
	philo_eat,
	philo_sleep,
	philo_think, 
	philo_dead
}				t_print_msg;

typedef struct	s_philo_shared_data {
	int				*eat_count;
	int				nb_philo;
	int				nb_forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
	int				death;
	struct timeval	*last_meal;
	sem_t			*forks_sem;
	sem_t			*fork_grab_sem;
	sem_t		 	*post_sem;
	struct timeval  start_time;
}				t_philo_shared_data;

typedef struct	s_philo_data {
	int					id;
	int					msg;
	t_philo_shared_data *shared_data;
}				t_philo_data;

int			clear_shared_data(t_philo_shared_data *shared_data, int mutex_arr_len);
void		*monitor_death(void *shared_data);
int			init_data(t_philo_shared_data *shared_data, int ac, char **av);
void		print_msg(pthread_mutex_t *print_mutex, int state, int id, int time);
int			check_input(int ac, char **av);
int			clear_shared_data(t_philo_shared_data *shared_data, int mutex_arr_len);
int			philo_create(t_philo_shared_data *shared_data, int id);
void		*philo_life(void *philo_data);
void		my_usleep(int micro, long long int start_time);
/*
** CHRONO
*/

int				chrono_start(struct timeval *timeval_s);
long long int	chrono_get_timeelapsed(struct timeval *start_time);
int				chrono_iselapsed(struct timeval *start_time, int microsec);
void			chrono_timer(struct timeval *start_time, int timer);
long long int	chrono_timeval_to_long(struct timeval *time);
#endif