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