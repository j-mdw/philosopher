/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 18:10:15 by jmaydew           #+#    #+#             */
/*   Updated: 2021/04/27 20:20:20 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int
	main(int ac, char **av)
{
	t_philo_shared_data shared_data;
	int					ret;

	if (!check_input(ac, av))
	{
		printf("Wrong input\n");
		return (EXIT_FAILURE);
	}
	if (!init_data(&shared_data, ac, av))
		return (EXIT_FAILURE);
	if (shared_data.nb_philo <= 1 || shared_data.time_to_die <= 0
	|| shared_data.max_eat == 0)
	{
		printf("Wrong input value\n");
		return (EXIT_FAILURE);
	}
	ret = philo_create(&shared_data, 1);
	if (ret == -1)
		return (clear_shared_data() + 1);
	else
		return (clear_shared_data());
}
