/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 17:22:05 by jmaydew           #+#    #+#             */
/*   Updated: 2021/04/29 10:51:19 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int
	write_nbr(unsigned int val, char *arr)
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
	ft_strcpy(char *src, char *cpy)
{
	int i;

	i = 0;
	while (src[i])
	{
		cpy[i] = src[i];
		i++;
	}
	cpy[i] = 0;
	return (i);
}

static void
	print_msg_stdout(int state, int id, int time_micro)
{
	static char print_arr[4096];
	int			index;
	static char *state_arr[5] = {
		"has taken a fork\n",
		"is eating\n",
		"is sleeping\n",
		"is thinking\n",
		"died\n"};

	index = write_nbr(time_micro / 1000, print_arr);
	print_arr[index++] = ' ';
	index += write_nbr(id, &print_arr[index]);
	print_arr[index++] = ' ';
	index += ft_strcpy(state_arr[state], &print_arr[index]);
	write(1, print_arr, index);
}

void
	print_msg(pthread_mutex_t *print_mutex, int state, int id, int time_micro)
{
	if (!g_philo_death || state == philo_dead)
	{
		if (state != philo_dead)
			pthread_mutex_lock(print_mutex);
		if (!g_philo_death || state == philo_dead)
		{
			if (state == philo_fork_eat)
			{
				print_msg_stdout(philo_fork, id, time_micro);
				print_msg_stdout(philo_eat, id, time_micro);
			}
			else
				print_msg_stdout(state, id, time_micro);
		}
		pthread_mutex_unlock(print_mutex);
	}
}
