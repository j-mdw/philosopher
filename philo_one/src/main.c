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
    return (0);
}

// void
//     init_philo_data(t_philo_shared_data *src, t_philo_shared_data *dst, int id)
// {
//     *dst = *src;
//     (void)id;
//     printf("src: %d|%d|%d|%d|%d|%d|%ld|%ld|%p|%p|%p\n", src->time_to_die, src->time_to_eat, src->time_to_sleep,
//     src->nb_philo, src->nb_forks, src->max_eat, src->start_time.tv_sec, src->start_time.tv_usec, src->mutex_arr, &src->nb_forks, &src->time_to_eat);
//     printf("dst: %d|%d|%d|%d|%d|%d|%ld|%ld|%p|%p|%p\n", dst->time_to_die, dst->time_to_eat, dst->time_to_sleep,
//     dst->nb_philo, dst->nb_forks, dst->max_eat, dst->start_time.tv_sec, dst->start_time.tv_usec, dst->mutex_arr, &dst->nb_forks, &dst->time_to_eat);
// }

int
    main(int ac, char **av)
{
    t_philo_shared_data shared_data;
    // t_philo_shared_data dst;

    if (!check_input(ac, av))
    {
        printf("Wrong input\n");
        return (EXIT_FAILURE);
    }
    if (!init_data(&shared_data, ac, av))
        return (EXIT_FAILURE);
    usleep(48000);
    printf("Is elapsed?: %d\n", chrono_iselapsed(&shared_data.start_time, 50000));
    // init_philo_data(&shared_data, &dst, 1);
    philo_create(&shared_data, 1);
    return (clear_shared_data(&shared_data, shared_data.nb_philo - 1));
}