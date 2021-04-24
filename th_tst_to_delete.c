#include <stdio.h>
#include <pthread.h>

typedef	struct s_val {
		int i;
		int j;
	} t_val;

void *func(void * data)
{
	int i = 0;

	while (i < 100)
	{
		((t_val *)data)->i++;
		printf("func t: %d\n", ((t_val *)data)->i);
	i++;
	}
	return (NULL);
}

main()
{
	pthread_t thread;
	t_val tval;

	tval.i = 0;
	tval.j = 1;

	pthread_create(&thread, NULL, func, (void *)&tval);
	while (tval.i < 100)
	{
		tval.i += 2;
		printf("Main i: %d\n", tval.i);
	}
	tval.j--;
	pthread_join(thread, NULL);
	}
