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
	t_philo_data	philo_data;
	pid_t			child;
	int				wstatus;

	if (id > shared_data->nb_philo)
		return (0);
	philo_data.id = id;
	philo_data.shared_data = shared_data;
	if ((child = fork()) < 0)
		return (-1);
	if (child == 0)
		philo_life(&philo_data);
	else
	{
		philo_create(shared_data, id + 1);
		waitpid(child, &wstatus, 0);
	}
	return (0);
}
