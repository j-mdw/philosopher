#include "philo_two.h"

// void
//     set_forks_index(int nb_forks, int philo_id, int *fork_1, int *fork_2)
// {
//     if (philo_id == 1)
//     {
//         *fork_1 = nb_forks - 1;
//         *fork_2 = 0;
//     }
//     else if (philo_id % 2)
//     {
//         *fork_1 = philo_id - 2;
//         *fork_2 = philo_id - 1;
//     }
//     else
//     {
//         *fork_1 = philo_id - 1;
//         *fork_2 = philo_id - 2;
//     }
// }

void
    philo_eating(t_philo_data *data, struct timeval *time)
{
    long long int time_elapsed;

    sem_wait(data->shared_data->fork_grab_sem);
    sem_wait(data->shared_data->forks_sem);
    print_msg(data->shared_data->print_sem, philo_fork, data->id,
        chrono_get_timeelapsed(&data->shared_data->start_time));
    // pthread_mutex_lock(&data->shared_data->mutex_arr[forks[0]]);        
    // pthread_mutex_lock(&data->shared_data->mutex_arr[forks[1]]);
    sem_wait(data->shared_data->forks_sem);
    sem_post(data->shared_data->fork_grab_sem);
    chrono_start(time);
    time_elapsed = chrono_get_timeelapsed(&data->shared_data->start_time);
    sem_wait(data->shared_data->post_sem);
    // pthread_mutex_lock(&data->shared_data->post_mutex);
    data->shared_data->last_meal[data->id - 1].tv_sec = time->tv_sec;
    data->shared_data->last_meal[data->id - 1].tv_usec = time->tv_usec;
    data->shared_data->eat_count[data->id - 1]++;
    sem_post(data->shared_data->post_sem);
    // pthread_mutex_unlock(&data->shared_data->post_mutex);
    print_msg(data->shared_data->print_sem, philo_fork, data->id,
    time_elapsed);
    print_msg(data->shared_data->print_sem, philo_eat, data->id,
    time_elapsed);
    chrono_timer(time, data->shared_data->time_to_eat);
    sem_post(data->shared_data->forks_sem);
    sem_post(data->shared_data->forks_sem);
    // pthread_mutex_unlock(&data->shared_data->mutex_arr[forks[0]]);
    // pthread_mutex_unlock(&data->shared_data->mutex_arr[forks[1]]);
}

void
    *philo_life(void *philo_data)
{
    struct timeval  time;
    t_philo_data    *data;
    // int             forks[2];
    int             i;

    data = (t_philo_data *)philo_data;
    if (data->id % 2)
        my_usleep(data->shared_data->time_to_eat / 2, chrono_timeval_to_long(&data->shared_data->start_time));
    // set_forks_index(data->shared_data->nb_forks, data->id, &forks[0], &forks[1]);
    i = data->shared_data->max_eat;
    while (i && !g_philo_death)
    {
        philo_eating(data, &time);
        print_msg(data->shared_data->print_sem, philo_sleep, data->id,
        chrono_get_timeelapsed(&data->shared_data->start_time));
        chrono_timer(&time, data->shared_data->time_to_eat + data->shared_data->time_to_sleep);
        print_msg(data->shared_data->print_sem, philo_think, data->id,
        chrono_get_timeelapsed(&data->shared_data->start_time));
        if (i > 0)
            i--;
        if (data->id % 2)
            usleep(300);
    }
    return (NULL);
}