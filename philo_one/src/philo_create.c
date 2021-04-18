#include "philo_one.h"

int
    philo_create(t_philo_shared_data *shared_data, int id)
{
    pthread_t       philo_thread;
    t_philo_data    philo_data;
    int             ret;

    if (id > shared_data->nb_philo)
        return (1);
    philo_data.id = id;
    philo_data.shared_data = shared_data;
    if (pthread_create(&philo_thread, NULL, philo_life, &philo_data) != 0) //Error management: should indicate to all process if an error occurs and they should all return!!
        return (0);
    ret = philo_create(shared_data, id + 1);
    pthread_join(philo_thread, NULL);
    return (ret);
}