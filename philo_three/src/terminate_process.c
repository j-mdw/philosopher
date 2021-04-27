/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 19:55:07 by jmaydew           #+#    #+#             */
/*   Updated: 2021/04/27 19:55:10 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void
	terminate_process(t_philo_data *data)
{
	sem_close(data->shared_data->post_sem);
	sem_unlink(data->msg);
	sem_close(data->shared_data->forks_sem);
	sem_close(data->shared_data->fork_grab_sem);
	sem_close(data->shared_data->print_sem);
	exit(0);
}
