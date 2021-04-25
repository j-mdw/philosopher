#include "philo_three.h"

int
	ft_strcpy(char *src, char *cpy)
{
	int i;

	i = 0;
	while (src[i])
	{
		cpy[i] = src[i];
		i++;
	}
	cpy[i] = 0;
	return (i);
}