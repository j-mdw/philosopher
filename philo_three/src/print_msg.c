/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 18:10:15 by jmaydew           #+#    #+#             */
/*   Updated: 2021/04/24 18:14:42 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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

void
	print_msg(sem_t *print_sem, int state, int id, int time_micro)
{
	static char print_arr[4096];
	int			index;
	static char *state_arr[5] = {
		"has taken a fork\n",
		"is eating\n",
		"is sleeping\n",
		"is thinking\n",
		"died\n"};

	// if (!g_philo_death || state == philo_dead)
	// {
		sem_wait(print_sem);
		// if (!g_philo_death || state == philo_dead)
		// {
			index = cpy_nbr(time_micro / 1000, print_arr);
			print_arr[index++] = ' ';
			index += cpy_nbr(id, &print_arr[index]);
			print_arr[index++] = ' ';
			index += ft_strcpy(state_arr[state], &print_arr[index]);
			write(1, print_arr, index);
		// }
		if (state != philo_dead)
			sem_post(print_sem);
	// }
}
