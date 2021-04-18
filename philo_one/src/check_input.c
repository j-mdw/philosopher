#include "philo_one.h"

int
    check_input(int ac, char **av)
{
    int i;
    int j;

    if (ac < 5 || ac > 6)
        return (0);
    i = 1;
    while (i < ac)
    {
        j = 0;
        while (av[i][j])
        {
            if (av[i][j] > '9' || av[i][j] < '0')
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}