/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 17:22:05 by jmaydew           #+#    #+#             */
/*   Updated: 2021/04/27 22:18:14 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int
	micro_curr_time(struct timeval *time)
{
	gettimeofday(time, NULL);
	return (chrono_timeval_to_long(time));
}

void
	my_usleep(int micro, int start_time)
{
	struct timeval current_time;

	while ((micro_curr_time(&current_time) - start_time) < micro)
	{
		usleep(200);
	}
}
