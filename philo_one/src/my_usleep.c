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

void
	my_usleep(int micro, long long int start_time)
{
	struct timeval current_time;

	while (1)
	{

		chrono_start(&current_time);
		if ((chrono_timeval_to_long(&current_time) - start_time) >= micro)
			return ;
		usleep(USLEEP_FRACTION);
	}
}
