/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 18:10:15 by jmaydew           #+#    #+#             */
/*   Updated: 2021/04/24 18:16:03 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void
	my_usleep(int micro, long long int start_time)
{
	struct timeval current_time;

	while (1)
	{
		usleep(USLEEP_FRACTION);
		chrono_start(&current_time);
		if ((chrono_timeval_to_long(&current_time) - start_time) >= micro)
			return ;
	}
}
