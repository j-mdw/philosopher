#include "philo_one.h"

int
    chrono_start(struct timeval *timeval_s)
{
    int err;
    if ((err = gettimeofday(timeval_s, NULL)) != 0)
    {
        return (0);
    }
    return (1);
}

long long int
    chrono_timeval_to_long(struct timeval *time)
{
    long long int   time_long;

    time_long = time->tv_sec * 1000000;
    time_long += time->tv_usec;
    return (time_long);
}

long long int
    chrono_get_timeelapsed(struct timeval *start_time)
{
    struct timeval  tod;
    long long int   time0;
    long long int   time1;

    if (gettimeofday(&tod, NULL) != 0)
        return (-1);
    time0 = chrono_timeval_to_long(start_time);
    time1 = chrono_timeval_to_long(&tod);
    return (time1 - time0);
}

int
    chrono_iselapsed(struct timeval *start_time, int microsec)
{
    long long int   elapsed;

    elapsed = chrono_get_timeelapsed(start_time);
    if (elapsed > microsec)
        return (1);
    return (0);
}

void
    chrono_timer(struct timeval *start_time, int timer)
{
    // long long int time;
    // struct timeval current_time;

    // chrono_start()
    // time = timer - chrono_get_timeelapsed(start_time);
    // if (time > 0)
        my_usleep(timer, chrono_timeval_to_long(start_time));
}