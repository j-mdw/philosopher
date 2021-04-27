#include "philo_three.h"

int
	philo_sem_open(t_philo_shared_data *data, char *name)
{
	if ((data->forks_sem = sem_open(FORKS_SEM, 0)) == SEM_FAILED)
		return (0);
	if ((data->fork_grab_sem = sem_open(FORK_GRAB_SEM, 0)) == SEM_FAILED)
		return (0);
	if ((data->print_sem = sem_open(PRINT_SEM, 0)) == SEM_FAILED)
		return (0);
	if ((data->post_sem = sem_open(name, O_CREAT | O_EXCL, SEM_MOD, 1))
	!= SEM_FAILED)
		return (1);
	sem_unlink(name);
	if ((data->post_sem = sem_open(name, O_CREAT, SEM_MOD, 1)) != SEM_FAILED)
		return (1);
	return (0);
}