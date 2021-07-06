#include "philo.h"

void	init_table(t_table *table)
{
	size_t	i;

	table->forks = (pthread_mutex_t *)malloc(sizeof (pthread_mutex_t)
			* table->numbers);
	i = -1;
	while (++i < table->numbers)
		pthread_mutex_init(&(table->forks[i]), NULL);
	pthread_mutex_init(&table->print, NULL);
}

void	inits_philosophers(t_phil *philosophers, size_t count)
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
}
