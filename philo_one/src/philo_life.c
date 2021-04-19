#include "philo_one.h"

void
    set_forks_index(int nb_forks, int philo_id, int *fork_1, int *fork_2)
{
    if (philo_id == 1)
    {
        *fork_1 = nb_forks - 1;
        *fork_2 = 0;
    }
    else if (philo_id % 2)
    {
        *fork_1 = philo_id - 2;
        *fork_2 = philo_id - 1;
    }
    else
    {
        *fork_1 = philo_id - 1;
        *fork_2 = philo_id - 2;
    }
}

void
    *philo_life(void *philo_data)
{
    struct timeval  time;
    t_philo_data    *philo_data_c;
    int             fork_1;
    int             fork_2;
    int             i;

    philo_data_c = (t_philo_data *)philo_data;
    set_forks_index(philo_data_c->shared_data->nb_forks, philo_data_c->id, &fork_1, &fork_2);
    i = philo_data_c->shared_data->max_eat;
    while (i)
    {
        pthread_mutex_lock(&philo_data_c->shared_data->mutex_arr[fork_1]);
        print_msg(&philo_data_c->shared_data->print_mutex, philo_fork,
            philo_data_c->id,
            chrono_get_timeelapsed(&philo_data_c->shared_data->start_time));        
        pthread_mutex_lock(&philo_data_c->shared_data->mutex_arr[fork_2]);
        chrono_start(&time);
        print_msg(&philo_data_c->shared_data->print_mutex, philo_fork, 
            philo_data_c->id,
            chrono_get_timeelapsed(&philo_data_c->shared_data->start_time));
        print_msg(&philo_data_c->shared_data->print_mutex, philo_eat, 
            philo_data_c->id,
            chrono_get_timeelapsed(&philo_data_c->shared_data->start_time));        
        chrono_timer(&time, philo_data_c->shared_data->time_to_eat);

        pthread_mutex_unlock(&philo_data_c->shared_data->mutex_arr[fork_1]);
        pthread_mutex_unlock(&philo_data_c->shared_data->mutex_arr[fork_2]);
        print_msg(&philo_data_c->shared_data->print_mutex, philo_sleep, philo_data_c->id,
        chrono_get_timeelapsed(&philo_data_c->shared_data->start_time));

        chrono_timer(&time, philo_data_c->shared_data->time_to_eat + philo_data_c->shared_data->time_to_sleep);
        print_msg(&philo_data_c->shared_data->print_mutex, philo_think, philo_data_c->id,
        chrono_get_timeelapsed(&philo_data_c->shared_data->start_time));
        if (i > 0)
            i--;
    }
    printf("Hello from philo %d\n", ((t_philo_data *)philo_data)->id);
    return (NULL);
}