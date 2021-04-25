#include <stdio.h>
#include <semaphore.h>
#include <string.h>

void
	print(char *s)
{
	printf("%s\n", s);
}

main()
{
	char *a = "/GHello";
	sem_t *sem;
	int err;

	sem = sem_open(a, O_CREAT | O_EXCL, 0664, 1);
	if (sem == SEM_FAILED)
		print("failed 1");
	if (sem_close(sem))
		perror("Sem close 1");
	sem = sem_open(a, O_CREAT);
	if (sem == SEM_FAILED)
		print("failed 2");
	perror("Err");
	if(sem_close(sem))
		perror("Sem close");
	if (sem_unlink(a))
		perror("Sem unlink");
	print("=bonjour");
}
