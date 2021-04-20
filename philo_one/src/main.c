#include "philo_one.h"

int
    clear_shared_data(t_philo_shared_data *shared_data, int mutex_arr_len)
{
    int i;

    i = 0;
    if (shared_data->mutex_arr)
    {
        while (i < mutex_arr_len)
        {
            pthread_mutex_destroy(&shared_data->mutex_arr[i]);
            i++;
        }
        free(shared_data->mutex_arr);
    }
    pthread_mutex_destroy(&shared_data->print_mutex); //This could fail if it was not initialized, but should not cause a segfault
    free(shared_data->last_meal);
    return (0);
}

void
    *monitor_death(void *shared_data)
{
    int                 i;
    int                 f;
    t_philo_shared_data *data;

    data = (t_philo_shared_data *)shared_data;
    f = 1;
    while (!data->death)
    {
        i = 0;
        while (i < data->nb_philo)
        {
            if (chrono_iselapsed(&data->last_meal[i], data->time_to_die))
            {
                print_msg(&data->print_mutex, philo_dead, i + 1,
                chrono_timeval_to_long(&data->last_meal[i]) + data->time_to_die
                - chrono_timeval_to_long(&data->start_time));
                data->death = 1;
                break;
            }
            i++;
        }
        usleep(1000);
    }
    return (NULL);
}

int
    main(int ac, char **av)
{
    t_philo_shared_data shared_data;
    pthread_t           monitor_th;

    if (!check_input(ac, av))
    {
        printf("Wrong input\n");
        return (EXIT_FAILURE);
    }
    if (!init_data(&shared_data, ac, av))
        return (EXIT_FAILURE);
    if (pthread_create(&monitor_th, NULL, monitor_death, &shared_data))
        return (clear_shared_data(&shared_data, shared_data.nb_forks) + 1);
    if (philo_create(&shared_data, 1))
        return (clear_shared_data(&shared_data, shared_data.nb_forks) + 1);
    pthread_join(monitor_th, NULL);
    return (clear_shared_data(&shared_data, shared_data.nb_forks));
}