#include "philo_one.h"

static int
    philo_atoi(char *s)
{
    int ret;
    int i;

    ret = 0;
    i = 0;
    while (s[i])
    {
        ret *= 10;
        ret += s[i] - '0';
        i++;
    }
    return (ret);
}

int
    init_data(t_philo_shared_data *shared_data, int ac, char **av)
{
    int i;

    shared_data->nb_philo = philo_atoi(av[1]);
    shared_data->nb_forks = shared_data->nb_philo;
    shared_data->time_to_die = philo_atoi(av[2]) * 1000;
    shared_data->time_to_eat = philo_atoi(av[3]) * 1000;
    shared_data->time_to_sleep = philo_atoi(av[4]) * 1000;
    shared_data->mutex_arr = NULL;

    if (ac == 6)
        shared_data->max_eat = philo_atoi(av[5]);
    else
        shared_data->max_eat = -1;
    if (pthread_mutex_init(&shared_data->print_mutex, NULL) != 0)
        return (clear_shared_data(shared_data, shared_data->nb_forks));
    if (!(shared_data->mutex_arr = (pthread_mutex_t *)malloc(
        sizeof(pthread_mutex_t) * shared_data->nb_forks)))
        return (0);
    i = 0;
    while (i < shared_data->nb_forks)
    {
        if (pthread_mutex_init(&shared_data->mutex_arr[i], NULL) != 0)
            return (clear_shared_data(shared_data, i));
        i++;
    }
    shared_data->dead_philo = 0;
    chrono_start(&shared_data->start_time);
    return (1);
}