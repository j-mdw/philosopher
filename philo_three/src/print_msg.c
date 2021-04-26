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

// int
// 	print_msg(sem_t *print_sem, int state, int id, int time_micro)
// {
// 	static char print_arr[4096];
// 	int			index;
// 	static char *state_arr[5] = {
// 		"has taken a fork\n",
// 		"is eating\n",
// 		"is sleeping\n",
// 		"is thinking\n",
// 		"died\n"};

// 	if (sem_wait(print_sem) != 0)
// 	{
// 		printf("Semwait failed: process %d\n", id);
// 		return (0);
// 	}
// 	if (state == philo_dead)
// 	{
// 		sem_close(print_sem);
// 		sem_unlink(PRINT_SEM);
// 		printf("Print sem unlinked\n");
// 	}
// 	index = cpy_nbr(time_micro / 1000, print_arr);
// 	print_arr[index++] = ' ';
// 	index += cpy_nbr(id, &print_arr[index]);
// 	print_arr[index++] = ' ';
// 	index += ft_strcpy(state_arr[state], &print_arr[index]);
// 	write(1, print_arr, index);
// 	if (state != philo_dead)
// 		sem_post(print_sem);
// 	return (1);
// }

int
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
	sem_t	*p_sem;
	
	// printf("About to grab print sem: %d\n", id);
	sem_wait(print_sem);
	// printf("Print sem grabbed: %d\n", id);
	p_sem = sem_open(DEATH_SEM, 0);
	if (p_sem == SEM_FAILED)
	{
		sem_post(print_sem);
		// printf("Sem failed - death sem - %d\n", id); //DEBUG
		return (0);
	}
	sem_close(p_sem);
	if (state == philo_dead)
	{
		sem_unlink(DEATH_SEM);
		// printf("p_sem unlinked: %d\n", id);
	}
	index = cpy_nbr(time_micro / 1000, print_arr);
	print_arr[index++] = ' ';
	index += cpy_nbr(id, &print_arr[index]);
	print_arr[index++] = ' ';
	index += ft_strcpy(state_arr[state], &print_arr[index]);
	write(1, print_arr, index);
	sem_post(print_sem);
	return (1);
}
