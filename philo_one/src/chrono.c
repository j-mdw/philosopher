#include "philo_one.h"

int
    chrono_start(struct timeval *timeval_s)
{
    if (gettimeofday(timeval_s, NULL) != 0)
        return (0);
    // printf("%ld|%ld|\n", timeval_s->tv_sec, timeval_s->tv_usec);
    return (1);
}

long long int
    chrono_get_timeelapsed(struct timeval *start_time)
{
    struct timeval  tod;
    long long int   time0;
    long long int   time1;

    if (gettimeofday(&tod, NULL) != 0)
        return (-1);
    time0 = start_time->tv_sec * 1000000;
    time0 += start_time->tv_usec;

    time1 = tod.tv_sec * 1000000;
    time1 += tod.tv_usec;
    return (time1 - time0);
}

int
    chrono_iselapsed(struct timeval *start_time, int microsec)
{
    // struct timeval  tod;
    long long int   elapsed;
    // long long int   time1;

    // if (gettimeofday(&tod, NULL) != 0)
    //     return (-1);
    // time0 = start_time->tv_sec * 1000000;
    // time0 += start_time->tv_usec;

    // time1 = tod.tv_sec * 1000000;
    // time1 += tod.tv_usec;
    elapsed = chrono_get_timeelapsed(start_time);
    if (elapsed > microsec)
        return (1);
    return (0);
}