#include "philo_one.h"

/*
** If no philo died, try to grab forks
** If only one fork available, print the message and try to grab the other one
** check that no one is dead before each print ::: /!\ careful with waits on print mutex (print funciton should always check there's no death???)
*/

int
    grab_fork_1(pthread_mutex_t *forks, int nb_forks, int philo_id)
{
    int fork_1;

    if (philo_id == 1)
        fork_1 = nb_forks - 1;
    else if (philo_id % 2)
        fork_1 = philo_id - 2;
    else
        fork_1 = philo_id - 1;
    pthread_mutex_lock(&forks[fork_1]);
    return (fork_1);
}

void
    *philo_life(void *philo_data)
{
    // pthread_t       print_thread;
    t_philo_data    *philo_data_c;
    int             fork_1;

    philo_data_c = (t_philo_data *)philo_data;
    int i = 0;
    while (i < 3)
    {
        fork_1 = grab_fork_1(philo_data_c->shared_data->mutex_arr, philo_data_c->shared_data->nb_forks, philo_data_c->id);
            print_msg(&philo_data_c->shared_data->print_mutex, philo_fork, philo_data_c->id, 101);
        pthread_mutex_unlock(&philo_data_c->shared_data->mutex_arr[fork_1]);
        i++;
    }
    printf("Hello from philo %d\n", ((t_philo_data *)philo_data)->id);
    return (NULL);
}