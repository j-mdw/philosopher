#include "philo_two.h"

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

static void
    set_last_meal(t_philo_shared_data *shared_data)
{
    int i;

    i = 0;
    while (i < shared_data->nb_philo)
    {
        (shared_data->last_meal[i]).tv_sec = shared_data->start_time.tv_sec;
        (shared_data->last_meal[i]).tv_usec = shared_data->start_time.tv_usec;
        i++;
    }
}

static void
    init_shared_data(t_philo_shared_data *shared_data, int ac, char **av)
{
    shared_data->nb_philo = philo_atoi(av[1]);
    shared_data->nb_forks = shared_data->nb_philo;
    shared_data->time_to_die = philo_atoi(av[2]) * 1000;
    shared_data->time_to_eat = philo_atoi(av[3]) * 1000;
    shared_data->time_to_sleep = philo_atoi(av[4]) * 1000;
    shared_data->eat_count = NULL;
    shared_data->mutex_arr = NULL;
    shared_data->last_meal = NULL;
    g_philo_death = 0;
    if (ac == 6)
        shared_data->max_eat = philo_atoi(av[5]);
    else
        shared_data->max_eat = -1;
}

int
    init_data(t_philo_shared_data *shared_data, int ac, char **av)
{
    int i;

    init_shared_data(shared_data, ac, av);
    if (shared_data->forks_sem = sem_open(FORKS_SEM, O_CREAT, shared_data->nb_forks,))


    if (pthread_mutex_init(&shared_data->print_mutex, NULL) != 0)
        return (clear_shared_data(shared_data, shared_data->nb_forks));
    if (pthread_mutex_init(&shared_data->post_mutex, NULL) != 0)
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
    if (!(shared_data->last_meal = (struct timeval *)malloc(sizeof(struct timeval) * shared_data->nb_philo)))
        return (clear_shared_data(shared_data, shared_data->nb_forks));
    chrono_start(&shared_data->start_time);
    set_last_meal(shared_data);
    if (!(shared_data->eat_count = (int *)malloc(sizeof(int) * shared_data->nb_philo)))
        return (clear_shared_data(shared_data, shared_data->nb_forks));
    memset(shared_data->eat_count, 0, shared_data->nb_philo * sizeof(int));
    return (1);
}