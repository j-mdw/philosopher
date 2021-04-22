#include "philo_two.h"

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
    pthread_mutex_destroy(&shared_data->post_mutex);
    free(shared_data->last_meal);
    free(shared_data->eat_count);
    return (0);
}