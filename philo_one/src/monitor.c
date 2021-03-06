/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 17:22:05 by jmaydew           #+#    #+#             */
/*   Updated: 2021/04/24 17:56:03 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int
	all_done(int *eat_count, int max_eat, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (eat_count[i] < max_eat)
			return (0);
		i++;
	}
	return (1);
}

static int
	check_death(t_philo_shared_data *data, int index)
{
	pthread_mutex_lock(&data->post_mutex);
	pthread_mutex_lock(&data->print_mutex);
	if (chrono_iselapsed(&data->last_meal[index], data->time_to_die) &&
	((data->max_eat == -1) || (data->eat_count[index] < data->max_eat)))
	{
		g_philo_death = 1;
		print_msg(&data->print_mutex, philo_dead, index + 1,
		chrono_timeval_to_long(&data->last_meal[index]) + data->time_to_die
		- chrono_timeval_to_long(&data->start_time));
		pthread_mutex_unlock(&data->post_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_unlock(&data->post_mutex);
	return (0);
}

void
	*monitor_death(void *shared_data)
{
	int					i;
	t_philo_shared_data *data;

	data = (t_philo_shared_data *)shared_data;
	while (!g_philo_death)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (check_death(data, i))
				return (NULL);
			i++;
		}
		if (data->max_eat != -1 && all_done(data->eat_count, data->max_eat,
		data->nb_philo))
		{
			g_philo_death = 1;
			return (NULL);
		}
		usleep(MONITOR_SLEEP);
	}
	return (NULL);
}
