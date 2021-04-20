#include "philo_one.h"

void
    print_msg(pthread_mutex_t *print_mutex, int state, int id, int time)
{
    static char *state_arr[5] = {
        "has taken a fork",
        "is eating",
        "is sleeping",
        "is thinking",
        "died"};
    // static int death = 0;

    if (!g_philo_death || state == philo_dead)
    {
        pthread_mutex_lock(print_mutex);
        if (!g_philo_death || state == philo_dead)
        {    printf("%d %d %s\n", time / 1000, id, state_arr[state]);


        }
        // if (state == philo_dead)
        //     death = 1;
        // if (state != philo_dead)
            pthread_mutex_unlock(print_mutex);
    }
}

    