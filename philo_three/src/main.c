/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 18:10:15 by jmaydew           #+#    #+#             */
/*   Updated: 2021/04/24 18:21:38 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int
	main(int ac, char **av)
{
	t_philo_shared_data shared_data;
	pthread_t			monitor_th;

	if (!check_input(ac, av))
	{
		printf("Wrong input\n");
		return (EXIT_FAILURE);
	}
	if (!init_data(&shared_data, ac, av))
		return (EXIT_FAILURE);
	if (shared_data.nb_philo <= 1)
	{	printf("Not enough philosophers\n");
		return (EXIT_FAILURE);
	}
	if (pthread_create(&monitor_th, NULL, monitor_death, &shared_data))
		return (clear_shared_data(&shared_data) + 1);
	if (philo_create(&shared_data, 1))
		return (clear_shared_data(&shared_data) + 1);
	pthread_join(monitor_th, NULL);
	return (clear_shared_data(&shared_data));
}
