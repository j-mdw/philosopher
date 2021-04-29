/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 18:10:15 by jmaydew           #+#    #+#             */
/*   Updated: 2021/04/27 19:55:48 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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

	index = cpy_nbr(time_micro / 1000, print_arr);
	print_arr[index++] = ' ';
	index += cpy_nbr(id, &print_arr[index]);
	print_arr[index++] = ' ';
	index += ft_strcpy(state_arr[state], &print_arr[index]);
	write(1, print_arr, index);
}

int
	print_msg(sem_t *print_sem, int state, int id, int time_micro)
{
	sem_t	*p_sem;

	if (state != philo_dead)
		sem_wait(print_sem);
	p_sem = sem_open(DEATH_SEM, 0);
	if (p_sem == SEM_FAILED)
	{
		sem_post(print_sem);
		return (0);
	}
	sem_close(p_sem);
	if (state == philo_dead)
		sem_unlink(DEATH_SEM);
	if (state == philo_fork_eat)
	{
		print_msg_stdout(philo_fork, id, time_micro);
		print_msg_stdout(philo_eat, id, time_micro);
	}
	else
		print_msg_stdout(state, id, time_micro);
	sem_post(print_sem);
	return (1);
}
