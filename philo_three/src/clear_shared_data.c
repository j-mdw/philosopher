/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_shared_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 18:10:15 by jmaydew           #+#    #+#             */
/*   Updated: 2021/04/27 19:57:36 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int
	sem_clear(void)
{
	int ret;

	ret = 0;
	ret += sem_unlink(FORKS_SEM);
	ret += sem_unlink(FORK_GRAB_SEM);
	ret += sem_unlink(PRINT_SEM);
	sem_unlink(DEATH_SEM);
	return (ret);
}

int
	clear_shared_data(void)
{
	return (sem_clear());
}
