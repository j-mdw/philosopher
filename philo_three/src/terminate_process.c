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
	// sem_unlink(FORKS_SEM);
	if(sem_close(data->shared_data->fork_grab_sem))
		printf("Process: %d: %s\n", data->id, strerror(errno));
	// sem_unlink(FORK_GRAB_SEM);
	// if(sem_close(data->shared_data->death_sem))
	// 	printf("Process: %d: %s\n", data->id, strerror(errno));
	// sem_unlink(DEATH_SEM);
	if(sem_close(data->shared_data->print_sem))
		printf("Process: %d: %s\n", data->id, strerror(errno));
	printf("Closing process: %d\n", data->id);
	// sem_unlink(PRINT_SEM);
	exit(0);
}