#include "philo_one.h"

int
    chrono_start(struct timeval *timeval_s)
{
    if (gettimeofday(timeval_s, NULL) != 0)
        return (0);
    printf("%ld|%ld|\n", timeval_s->tv_sec, timeval_s->tv_usec);
    return (1);
}

int
    chrono_iselapsed(struct timeval *start_time, int microsec)
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
    if ((time1 - time0) > microsec)
        return (1);
    return (0);
}