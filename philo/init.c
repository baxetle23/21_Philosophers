#include "philo.h"

int	init_table(t_table *table)
{
	size_t	i;

	table->forks = (pthread_mutex_t *)malloc(sizeof (pthread_mutex_t)
			* table->numbers);
	if (table->forks == NULL)
		return (1);
	i = -1;
	while (++i < table->numbers)
		if (pthread_mutex_init(&(table->forks[i]), NULL))
			return (1);
	if (pthread_mutex_init(&table->print, NULL))
		return (1);
	return (0);
}

int	inits_philosophers(t_phil *philosophers, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		philosophers[i].left_fork = i;
		philosophers[i].right_fork = i + 1;
		philosophers[i].name = i;
		if (i == count - 1)
			philosophers[i].right_fork = 0;
		i++;
	}
	return (0);
}
