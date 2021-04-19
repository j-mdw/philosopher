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

    pthread_mutex_lock(print_mutex);
    printf("%d %d %s\n", time / 1000, id, state_arr[state]);
    if (state != philo_dead)
        pthread_mutex_unlock(print_mutex);
}

    