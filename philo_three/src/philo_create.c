/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 18:10:15 by jmaydew           #+#    #+#             */
/*   Updated: 2021/04/24 18:15:08 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int
	philo_create(t_philo_shared_data *shared_data, int id)
{
	pthread_t		philo_thread;
	t_philo_data	philo_data;

	if (id > shared_data->nb_philo)
		return (0);
	philo_data.id = id;
	philo_data.shared_data = shared_data;
	if (pthread_create(&philo_thread, NULL, philo_life, &philo_data))
		return (-1);
	if (philo_create(shared_data, id + 1))
		return (-1);
	pthread_join(philo_thread, NULL);
	return (0);
}
