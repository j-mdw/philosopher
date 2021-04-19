#include "philo_one.h"

/*
** If no philo died, try to grab forks
** If only one fork available, print the message and try to grab the other one
** check that no one is dead before each print ::: /!\ careful with waits on print mutex (print funciton should always check there's no death???)
*/

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
    *philo_subthread_print(void *philo_data)
{
    print_msg(&((t_philo_data *)philo_data)->shared_data->print_mutex,
    ((t_philo_data *)philo_data)->msg, ((t_philo_data *)philo_data)->id,
    chrono_get_timeelapsed(&((t_philo_data *)philo_data)->shared_data->start_time));
}

void
    *philo_life(void *philo_data)
{
    pthread_t       print_thread;
    t_philo_data    *philo_data_c;
    int             fork_1;
    int             fork_2;

    philo_data_c = (t_philo_data *)philo_data;
    set_forks_index(philo_data_c->shared_data->nb_forks, philo_data_c->id, &fork_1, &fork_2);
    int i = 0;
    while (i < 3)
    {
        pthread_mutex_lock(&philo_data_c->shared_data->mutex_arr[fork_1]);
        print_msg(&philo_data_c->shared_data->print_mutex, philo_fork, 
            philo_data_c->id,
            chrono_get_timeelapsed(&philo_data_c->shared_data->start_time));        
        pthread_mutex_lock(&philo_data_c->shared_data->mutex_arr[fork_2]);
        print_msg(&philo_data_c->shared_data->print_mutex, philo_fork, 
            philo_data_c->id,
            chrono_get_timeelapsed(&philo_data_c->shared_data->start_time));
        print_msg(&philo_data_c->shared_data->print_mutex, philo_eat, 
            philo_data_c->id,
            chrono_get_timeelapsed(&philo_data_c->shared_data->start_time));        
        usleep(philo_data_c->shared_data->time_to_eat);
        pthread_mutex_unlock(&philo_data_c->shared_data->mutex_arr[fork_1]);
        printf("%d dropped fork %d\n", philo_data_c->id, fork_1 + 1);
        pthread_mutex_unlock(&philo_data_c->shared_data->mutex_arr[fork_2]);
        printf("%d dropped fork %d\n", philo_data_c->id, fork_2 + 1);
        usleep(1000);
        i++;
    }
    printf("Hello from philo %d\n", ((t_philo_data *)philo_data)->id);
    return (NULL);
}