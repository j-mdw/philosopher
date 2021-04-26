#include "philo_three.h"

void
	terminate_process(t_philo_data *data)
{
	sem_close(data->shared_data->post_sem);
	sem_unlink(data->msg);
	//kill(0, SIGTERM);
	exit(0);
}