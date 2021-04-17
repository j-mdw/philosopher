#include "philo_one.h"

int
    chrono_start(struct timeval *timeval_s)
{
    if (gettimeofday(timeval_s, NULL) != 0)
        return (0);
    printf("%ld|%d|\n", timeval_s->tv_sec, timeval_s->tv_usec);
    return (1);
}

// int
//     chrono_iselapsed(struct timeval *start_time, int milisec)
// {
//     struct timeval tod;

//     if (gettimeofday(&tod, NULL) != 0)
//         return (-1);
// }

int
    check_input(int ac, char **av)
{
    int i;
    int j;

    if (ac < 5 || ac > 6)
        return (0);
    i = 1;
    while (i < ac)
    {
        j = 0;
        while (av[i][j])
        {
            if (av[i][j] > '9' || av[i][j] < '0')
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}

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

static int
    init_fatal(t_philo_shared_data *shared_data, int err_index)
{
    int i;

    i = 0;
    while (i < err_index)
    {
        pthread_mutex_destroy(&shared_data->mutex_arr[i]);
        i++;
    }
    free(shared_data->mutex_arr);
    return (0);
}

int
    init_data(t_philo_shared_data *shared_data, int ac, char **av)
{
    int i;

    shared_data->nb_philo = philo_atoi(av[1]);
    shared_data->time_to_die = philo_atoi(av[2]);
    shared_data->time_to_eat = philo_atoi(av[3]);
    shared_data->time_to_sleep = philo_atoi(av[4]);
    if (ac == 6)
        shared_data->max_eat = philo_atoi(av[5]);
    else
        shared_data->max_eat = -1;
    if (!(shared_data->mutex_arr = (pthread_mutex_t *)malloc(
        sizeof(pthread_mutex_t) * shared_data->nb_philo)))
        return (0);
    i = 0;
    while (i < shared_data->nb_philo)
    {
        if (pthread_mutex_init(&shared_data->mutex_arr[i], NULL) != 0)
            return (init_fatal(shared_data, i));
        i++;
    }
    if (pthread_mutex_init(&shared_data->print_mutex, NULL) != 0)
        return (init_fatal(shared_data, i - 1));
    return (1);
}

int
    main(int ac, char **av)
{
    t_philo_shared_data shared_data;
    
    if (!check_input(ac, av))
    {
        printf("Wrong input\n");
        return (EXIT_FAILURE);
    }
    if (!init_data(&shared_data, ac, av))
        return (EXIT_FAILURE);
    // printf("%d|%d|%d|%d|\n", shared_data.nb_philo, shared_data.time_to_die,
    // shared_data.time_to_eat, shared_data.time_to_sleep);
    chrono_start();
    return (init_fatal(&shared_data, shared_data.nb_philo - 1));
}