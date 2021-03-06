/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 18:10:15 by jmaydew           #+#    #+#             */
/*   Updated: 2021/04/27 20:20:52 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
	set_first_meal(t_philo_shared_data *shared_data)
{
	shared_data->last_meal.tv_sec = shared_data->start_time.tv_sec;
	shared_data->last_meal.tv_usec = shared_data->start_time.tv_usec;
}

static void
	init_shared_data(t_philo_shared_data *shared_data, int ac, char **av)
{
	shared_data->nb_philo = philo_atoi(av[1]);
	shared_data->nb_forks = shared_data->nb_philo;
	shared_data->time_to_die = philo_atoi(av[2]) * 1000;
	shared_data->time_to_eat = philo_atoi(av[3]) * 1000;
	shared_data->time_to_sleep = philo_atoi(av[4]) * 1000;
	shared_data->forks_sem = NULL;
	shared_data->fork_grab_sem = NULL;
	shared_data->post_sem = NULL;
	shared_data->print_sem = NULL;
	shared_data->death_sem = NULL;
	shared_data->eat_count = 0;
	if (ac == 6)
		shared_data->max_eat = philo_atoi(av[5]);
	else
		shared_data->max_eat = -1;
}

static sem_t
	*sem_open_check(char *name, int size)
{
	sem_t	*sem;

	if ((sem = sem_open(name, O_CREAT | O_EXCL, SEM_MOD, size)) != SEM_FAILED)
		return (sem);
	sem_unlink(name);
	if ((sem = sem_open(name, O_CREAT, SEM_MOD, size)) != SEM_FAILED)
		return (sem);
	return (NULL);
}

int
	init_data(t_philo_shared_data *shared_data, int ac, char **av)
{
	init_shared_data(shared_data, ac, av);
	if (!(shared_data->forks_sem = sem_open_check(FORKS_SEM,
		shared_data->nb_forks)))
		return (clear_shared_data());
	sem_close(shared_data->forks_sem);
	if (!(shared_data->fork_grab_sem = sem_open_check(FORK_GRAB_SEM, 1)))
		return (clear_shared_data());
	sem_close(shared_data->fork_grab_sem);
	if (!(shared_data->print_sem = sem_open_check(PRINT_SEM, 1)))
		return (clear_shared_data());
	sem_close(shared_data->print_sem);
	if (!(shared_data->death_sem = sem_open_check(DEATH_SEM, 1)))
		return (clear_shared_data());
	sem_close(shared_data->death_sem);
	chrono_start(&shared_data->start_time);
	set_first_meal(shared_data);
	return (1);
}
