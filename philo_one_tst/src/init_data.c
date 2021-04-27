/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 17:22:05 by jmaydew           #+#    #+#             */
/*   Updated: 2021/04/24 18:00:28 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int
	philo_atoi(char *s)
{
	int ret;
	int i;

	ret = 0;
	i = 0;
	while (s[i])
	{
		ret *= 10;
		ret += s[i] - '0';
		i++;
	}
	return (ret);
}

static void
	set_last_meal(t_philo_shared_data *shared_data)
{
	int i;

	i = 0;
	while (i < shared_data->nb_philo)
	{
		(shared_data->last_meal[i]).tv_sec = shared_data->start_time.tv_sec;
		(shared_data->last_meal[i]).tv_usec = shared_data->start_time.tv_usec;
		i++;
	}
}

static void
	init_shared_data(t_philo_shared_data *shared_data, int ac, char **av)
{
	shared_data->nb_philo = philo_atoi(av[1]);
	shared_data->nb_forks = shared_data->nb_philo;
	shared_data->time_to_die = philo_atoi(av[2]);
	shared_data->time_to_eat = philo_atoi(av[3]);
	shared_data->time_to_sleep = philo_atoi(av[4]);
	shared_data->eat_count = NULL;
	shared_data->mutex_arr = NULL;
	shared_data->last_meal = NULL;
	g_philo_death = 0;
	if (ac == 6)
		shared_data->max_eat = philo_atoi(av[5]);
	else
		shared_data->max_eat = -1;
}

int
	init_data(t_philo_shared_data *data, int ac, char **av)
{
	int i;

	init_shared_data(data, ac, av);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (clear_shared_data(data, data->nb_forks));
	if (pthread_mutex_init(&data->post_mutex, NULL) != 0)
		return (clear_shared_data(data, data->nb_forks));
	if (!(data->mutex_arr = (pthread_mutex_t *)malloc(
		sizeof(pthread_mutex_t) * data->nb_forks)))
		return (0);
	i = -1;
	while (++i < data->nb_forks)
	{
		if (pthread_mutex_init(&data->mutex_arr[i], NULL) != 0)
			return (clear_shared_data(data, i));
	}
	if (!(data->last_meal = (struct timeval *)malloc(sizeof(struct timeval) *
	data->nb_philo)))
		return (clear_shared_data(data, data->nb_forks));
	chrono_start(&data->start_time);
	set_last_meal(data);
	if (!(data->eat_count = (int *)malloc(sizeof(int) * data->nb_philo)))
		return (clear_shared_data(data, data->nb_forks));
	memset(data->eat_count, 0, data->nb_philo * sizeof(int));
	return (1);
}
