#include "philo.h"

void	get_memory(pthread_t **t, t_phil **p, t_args **a, t_table *table)
{
	*t = (pthread_t *)malloc(sizeof(pthread_t) * table->numbers);
	*p = (t_phil *)malloc(sizeof(t_phil) * table->numbers);
	*a = (t_args *)malloc(sizeof(t_args) * table->numbers);
}

void	free_memory(pthread_t **t, t_phil **p, t_args **a, t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->numbers)
		pthread_detach((*t)[i]);
	free(*t);
	free(*p);
	free(*a);
	free(table->forks);
}
