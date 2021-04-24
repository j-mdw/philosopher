/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_shared_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 18:10:15 by jmaydew           #+#    #+#             */
/*   Updated: 2021/04/24 18:20:27 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int
	sem_clear(t_philo_shared_data *shared_data)
{
	int ret;

	ret = 0;
	if (shared_data->forks_sem)
	{
		sem_close(shared_data->forks_sem);
		ret += sem_unlink(FORKS_SEM);
	}
	if (shared_data->fork_grab_sem)
	{
		sem_close(shared_data->fork_grab_sem);
		ret += sem_unlink(FROK_GRAB_SEM);
	}
	if (shared_data->post_sem)
	{
		sem_close(shared_data->post_sem);
		ret += sem_unlink(POST_SEM);
	}
	if (shared_data->print_sem)
	{
		sem_close(shared_data->print_sem);
		ret += sem_unlink(PRINT_SEM);
	}
	return (ret);
}

int
	clear_shared_data(t_philo_shared_data *shared_data)
{
	if (sem_clear(shared_data) != 0)
		printf("Error clearing semaphores\n");
	free(shared_data->last_meal);
	free(shared_data->eat_count);
	return (0);
}
