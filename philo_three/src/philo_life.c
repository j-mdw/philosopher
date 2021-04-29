/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 18:10:15 by jmaydew           #+#    #+#             */
/*   Updated: 2021/04/29 10:53:24 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int
	send_print(t_philo_data *data, int state)
{
	if (!print_msg(data->shared_data->print_sem, state, data->id,
	chrono_get_timeelapsed(&data->shared_data->start_time)))
		return (0);
	return (1);
}

int
	philo_eating_2(t_philo_data *data, struct timeval *time,
	long long int timefe)
{
	if (!print_msg(data->shared_data->print_sem, philo_fork_eat, data->id,
		timefe))
	{
		sem_post(data->shared_data->forks_sem);
		sem_post(data->shared_data->forks_sem);
		return (0);
	}
	chrono_timer(time, data->shared_data->time_to_eat);
	sem_post(data->shared_data->forks_sem);
	sem_post(data->shared_data->forks_sem);
	if (data->shared_data->eat_count == data->shared_data->max_eat)
		return (0);
	return (1);
}

int
	philo_eating_1(t_philo_data *data, struct timeval *time)
{
	long long int time_elapsed;

	sem_wait(data->shared_data->fork_grab_sem);
	sem_wait(data->shared_data->forks_sem);
	if (!send_print(data, philo_fork))
	{
		sem_post(data->shared_data->forks_sem);
		sem_post(data->shared_data->fork_grab_sem);
		return (0);
	}
	sem_wait(data->shared_data->forks_sem);
	sem_post(data->shared_data->fork_grab_sem);
	chrono_start(time);
	time_elapsed = chrono_get_timeelapsed(&data->shared_data->start_time);
	sem_wait(data->shared_data->post_sem);
	data->shared_data->last_meal.tv_sec = time->tv_sec;
	data->shared_data->last_meal.tv_usec = time->tv_usec;
	data->shared_data->eat_count++;
	sem_post(data->shared_data->post_sem);
	if (!(philo_eating_2(data, time, time_elapsed)))
		return (0);
	return (1);
}

static int
	philo_init_param(char *sem_name, t_philo_data *data, pthread_t *monitor_th)
{
	int i;

	i = ft_strcpy(POST_SEM, sem_name);
	i += cpy_nbr(data->id, &sem_name[i]);
	sem_name[i] = 0;
	data->msg = sem_name;
	if (!philo_sem_open(data->shared_data, sem_name))
		return (0);
	if ((pthread_create(monitor_th, NULL, monitor_death, data) != 0))
		return (0);
	if (data->id % 2)
	{
		print_msg(data->shared_data->print_sem, philo_think, data->id,
		chrono_get_timeelapsed(&data->shared_data->start_time));
		my_usleep(data->shared_data->time_to_eat / 2,
		chrono_timeval_to_long(&data->shared_data->start_time));
	}
	return (1);
}

int
	philo_life(t_philo_data *data)
{
	pthread_t		monitor_th;
	struct timeval	time;
	int				i;
	char			sem_name[64];

	if (!philo_init_param(sem_name, data, &monitor_th))
		return (-1);
	i = data->shared_data->max_eat;
	while (i)
	{
		if (!philo_eating_1(data, &time))
			break ;
		if (!send_print(data, philo_sleep))
			break ;
		chrono_timer(&time, data->shared_data->time_to_eat +
		data->shared_data->time_to_sleep);
		if (!send_print(data, philo_think))
			break ;
		i += (-1 * (i > 0));
	}
	pthread_join(monitor_th, NULL);
	terminate_process(data);
	return (0);
}
