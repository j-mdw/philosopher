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
    while (1)
    {

    }
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
    if (!(pthread_create(&monitor_th, NULL, monitor_death, &shared_data)))
        return (clear_shared_data(&shared_data, shared_data.nb_forks) + 1);
    philo_create(&shared_data, 1);
    return (clear_shared_data(&shared_data, shared_data.nb_forks));
}