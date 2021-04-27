/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 18:10:15 by jmaydew           #+#    #+#             */
/*   Updated: 2021/04/25 22:32:20 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int
	check_death(t_philo_shared_data *data, int id)
{
	sem_wait(data->post_sem);
	if (chrono_iselapsed(&data->last_meal, data->time_to_die) &&
	((data->max_eat == -1) || (data->eat_count < data->max_eat)))
	{
		print_msg(data->print_sem, philo_dead, id,
		chrono_timeval_to_long(&data->last_meal) + data->time_to_die
		- chrono_timeval_to_long(&data->start_time));
		sem_post(data->post_sem);
		return (1);
	}
	sem_post(data->post_sem);
	return (0);
}

void
	*monitor_death(void *shared_data)
{
	t_philo_data 	*data;

	data = (t_philo_data *)shared_data;
	while ((data->shared_data->max_eat == -1) || 
	data->shared_data->eat_count < data->shared_data->max_eat)
	{
		if (check_death(data->shared_data, data->id))
			break ;
		if (data->shared_data->max_eat != -1 &&
		data->shared_data->eat_count == data->shared_data->max_eat)
			break ;
		usleep(data->shared_data->time_to_die / 10);
	}
	return (NULL);
}
