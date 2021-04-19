#include "philo_one.h"

int
    print_msg(pthread_mutex_t *print_mutex, int state, int id, int time)
{
    static char *state_arr[5] = {
        "has taken a fork",
        "is eating",
        "is sleeping",
        "is thinking",
        "died"};

    (void)print_mutex;
    // if (pthread_mutex_lock(print_mutex) != 0)
        // return (0);
    printf("%d %d %s\n", time / 1000, id, state_arr[state]);
    // if (pthread_mutex_unlock(print_mutex) != 0)
        return (0);
    return (1);
}

    