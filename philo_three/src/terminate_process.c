#include "philo_three.h"
#include <errno.h>

void
	terminate_process(t_philo_data *data)
{
	// errno = 0;
	if(sem_close(data->shared_data->post_sem))
		printf("Process: %d: %s\n", data->id, strerror(errno));
	if(sem_unlink(data->msg))
		printf("Process: %d: %s\n", data->id, strerror(errno));
	if(sem_close(data->shared_data->forks_sem))
		printf("Process: %d: %s\n", data->id, strerror(errno));
	if(sem_close(data->shared_data->fork_grab_sem))
		printf("Process: %d: %s\n", data->id, strerror(errno));
	if(sem_close(data->shared_data->print_sem))
		printf("Process: %d: %s\n", data->id, strerror(errno));
	// if (errno != 0)
	// 	printf("Process %d: %s\n", data->id, strerror(errno));
	printf("Closing process: %d\n", data->id);
	exit(0);
}