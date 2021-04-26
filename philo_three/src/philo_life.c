/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 18:10:15 by jmaydew           #+#    #+#             */
/*   Updated: 2021/04/24 18:20:04 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void
	philo_eating(t_philo_data *data, struct timeval *time)
{
	long long int time_elapsed;

	sem_wait(data->shared_data->fork_grab_sem);
	sem_wait(data->shared_data->forks_sem);
	if (!print_msg(data->shared_data->print_sem, philo_fork, data->id,
		chrono_get_timeelapsed(&data->shared_data->start_time)))
		terminate_process(data);
	sem_wait(data->shared_data->forks_sem);
	sem_post(data->shared_data->fork_grab_sem);
	chrono_start(time);
	time_elapsed = chrono_get_timeelapsed(&data->shared_data->start_time);
	sem_wait(data->shared_data->post_sem);
	data->shared_data->last_meal.tv_sec = time->tv_sec;
	data->shared_data->last_meal.tv_usec = time->tv_usec;
	data->shared_data->eat_count++;
	sem_post(data->shared_data->post_sem);
	if (!print_msg(data->shared_data->print_sem, philo_fork, data->id,
	time_elapsed))
		terminate_process(data);
	if (!print_msg(data->shared_data->print_sem, philo_eat, data->id,
	time_elapsed))
		terminate_process(data);
	chrono_timer(time, data->shared_data->time_to_eat);
	sem_post(data->shared_data->forks_sem);
	sem_post(data->shared_data->forks_sem);
	if (data->shared_data->eat_count == data->shared_data->max_eat)
		terminate_process(data);
}

static int
	cpy_nbr(unsigned int val, char *arr)
{
	int i;
	int deci_level;
	int cpy;

	deci_level = 1;
	cpy = val;
	while (cpy /= 10)
		deci_level *= 10;
	i = 0;
	while (deci_level)
	{
		arr[i] = (val / deci_level) + '0';
		i++;
		val %= deci_level;
		deci_level /= 10;
	}
	return (i);
}

static int
	philo_sem_open(t_philo_shared_data *data, char *name)
{
	if ((data->forks_sem = sem_open(FORKS_SEM, 0)) == SEM_FAILED)
		return (0);
	if ((data->fork_grab_sem = sem_open(FROK_GRAB_SEM, 0)) == SEM_FAILED)
		return (0);
	if ((data->print_sem = sem_open(PRINT_SEM, 0)) == SEM_FAILED)
		return (0);
	if ((data->post_sem = sem_open(name, O_CREAT | O_EXCL, SEM_MOD, 1)) != SEM_FAILED)
		return (1);
	sem_unlink(name);
	if ((data->post_sem = sem_open(name, O_CREAT, SEM_MOD, 1)) != SEM_FAILED)
		return (1);
	return (0);
}

int
	philo_life(t_philo_data *data)
{
	pthread_t		monitor_th;
	struct timeval	time;
	int				i;
	char			sem_name[64];

	i = ft_strcpy(POST_SEM, sem_name);
	i += cpy_nbr(data->id, &sem_name[i]);
	sem_name[i] = 0;
	data->msg = sem_name;

	if (!philo_sem_open(data->shared_data, sem_name))
		return (-1);
	if ((pthread_create(&monitor_th, NULL, monitor_death, data) != 0))
		return (-1);
	// pthread_detach(monitor_th);
	if (data->id % 2)
		my_usleep(data->shared_data->time_to_eat / 2,
		chrono_timeval_to_long(&data->shared_data->start_time));
	i = data->shared_data->max_eat;
	while (i)
	{
		philo_eating(data, &time);
		if (!print_msg(data->shared_data->print_sem, philo_sleep, data->id,
		chrono_get_timeelapsed(&data->shared_data->start_time)))
			terminate_process(data);
		chrono_timer(&time, data->shared_data->time_to_eat +
		data->shared_data->time_to_sleep);
		if (!print_msg(data->shared_data->print_sem, philo_think, data->id,
		chrono_get_timeelapsed(&data->shared_data->start_time)))
			terminate_process(data);
		if (i > 0)
			i--;
		if (data->id % 2)
			usleep(300);
	}
	pthread_join(monitor_th, NULL);
	terminate_process(data);
	return (0);
}
