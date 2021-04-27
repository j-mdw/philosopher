/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chrono.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 17:22:05 by jmaydew           #+#    #+#             */
/*   Updated: 2021/04/24 18:04:00 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int
	chrono_timeval_to_long(struct timeval *time)
{
	int	micro;

	micro = time->tv_sec * 1000 + time->tv_usec / 1000;
	return (micro);
}

int
	chrono_get_timeelapsed(struct timeval *start_time)
{
	struct timeval	tod;
	int	time0;
	int	time1;

	if (gettimeofday(&tod, NULL) != 0)
		return (-1);
	time0 = chrono_timeval_to_long(start_time);
	time1 = chrono_timeval_to_long(&tod);
	return (time1 - time0);
}

int
	chrono_iselapsed(struct timeval *start_time, int microsec)
{
	int	elapsed;

	elapsed = chrono_get_timeelapsed(start_time);
	if (elapsed > microsec)
		return (1);
	return (0);
}

void
	chrono_timer(struct timeval *start_time, int timer)
{
	my_usleep(timer, chrono_timeval_to_long(start_time));
}
