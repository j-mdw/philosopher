/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 17:22:05 by jmaydew           #+#    #+#             */
/*   Updated: 2021/04/29 10:51:38 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void
	set_forks(int nb_forks, int philo_id, int *fork_1, int *fork_2)
{
	if (philo_id == 1)
	{
		*fork_1 = nb_forks - 1;
		*fork_2 = 0;
	}
	else if (philo_id % 2)
	{
		*fork_1 = philo_id - 2;
		*fork_2 = philo_id - 1;
	}
	else
	{
		*fork_1 = philo_id - 1;
		*fork_2 = philo_id - 2;
	}
}

static void
	philo_eating(t_philo_data *data, struct timeval *time, int *forks)
{
	long long int time_elapsed;

	pthread_mutex_lock(&data->shared_data->mutex_arr[forks[0]]);
	print_msg(&data->shared_data->print_mutex, philo_fork, data->id,
		chrono_get_timeelapsed(&data->shared_data->start_time));
	pthread_mutex_lock(&data->shared_data->mutex_arr[forks[1]]);
	chrono_start(time);
	time_elapsed = chrono_get_timeelapsed(&data->shared_data->start_time);
	pthread_mutex_lock(&data->shared_data->post_mutex);
	data->shared_data->last_meal[data->id - 1].tv_sec = time->tv_sec;
	data->shared_data->last_meal[data->id - 1].tv_usec = time->tv_usec;
	data->shared_data->eat_count[data->id - 1]++;
	pthread_mutex_unlock(&data->shared_data->post_mutex);
	print_msg(&data->shared_data->print_mutex, philo_fork_eat, data->id,
	time_elapsed);
	chrono_timer(time, data->shared_data->time_to_eat);
	pthread_mutex_unlock(&data->shared_data->mutex_arr[forks[0]]);
	pthread_mutex_unlock(&data->shared_data->mutex_arr[forks[1]]);
}

static void
	odd_philo_start(t_philo_data *data)
{
	print_msg(&data->shared_data->print_mutex, philo_think, data->id,
	chrono_get_timeelapsed(&data->shared_data->start_time));
	my_usleep(data->shared_data->time_to_eat / 2,
	chrono_timeval_to_long(&data->shared_data->start_time));
}

void
	*philo_life(void *philo_data)
{
	struct timeval	time;
	t_philo_data	*data;
	int				forks[2];
	int				i;

	data = (t_philo_data *)philo_data;
	set_forks(data->shared_data->nb_forks, data->id, &forks[0], &forks[1]);
	if (data->id % 2)
		odd_philo_start(data);
	i = data->shared_data->max_eat;
	while (i && !g_philo_death)
	{
		philo_eating(data, &time, forks);
		i -= (i > 0);
		if (i == 0)
			break ;
		print_msg(&data->shared_data->print_mutex, philo_sleep, data->id,
		chrono_get_timeelapsed(&data->shared_data->start_time));
		chrono_timer(&time, data->shared_data->time_to_eat +
		data->shared_data->time_to_sleep);
		print_msg(&data->shared_data->print_mutex, philo_think, data->id,
		chrono_get_timeelapsed(&data->shared_data->start_time));
		if (data->id % 2)
			usleep(500);
	}
	return (NULL);
}
