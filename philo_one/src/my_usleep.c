#include "philo_one.h"

void
    my_usleep(int micro, long long int start_time)
{
    struct timeval current_time;

    while (1)
    {
        usleep(100);
        chrono_start(&current_time);
        if ((chrono_timeval_to_long(&current_time) - start_time) >= micro)
{
        // printf("### Time slept: %lld ###\n", (chrono_timeval_to_long(&current_time) - start_time));
            return ;}
    }

}