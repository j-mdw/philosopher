#include <stdio.h>
#include <pthread.h>

volatile int g_val;

//pthread_mutex_t lock;

void
	*thread_func(void *val)
{
	int value = (int)val;

//	printf("Value from thread: %d\n", value);
//	pthread_mutex_lock(&lock);
	g_val += value;
//	pthread_mutex_unlock(&lock);

	return (NULL);
}

int
	main(void)
{
	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;
	int i = 1;

	g_val = 0;
//	pthread_mutex_init(&lock, NULL);
	while (i < 1000)
	{

		pthread_create(&thread1, NULL, thread_func, (void *)i);
		i++;
		pthread_create(&thread2, NULL, thread_func, (void *)i);
		i++;
		pthread_create(&thread3, NULL, thread_func, (void *)i);
		i++;
		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);
		pthread_join(thread3, NULL);
	}
//		pthread_mutex_destroy(&lock);
		printf("Expected result: %d\n", 1001 * (1000 / 2));
		printf("Actual result: %d\n", g_val);
	return (0);
}
