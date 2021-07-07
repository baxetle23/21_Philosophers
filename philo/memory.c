#include "philo.h"

int	get_memory(pthread_t **t, t_phil **p, t_args **a, t_table *table)
{
	*t = (pthread_t *)malloc(sizeof(pthread_t) * table->numbers);
	if (*t == NULL)
		return (1);
	*p = (t_phil *)malloc(sizeof(t_phil) * table->numbers);
	if (*p == NULL)
		return (1);
	*a = (t_args *)malloc(sizeof(t_args) * table->numbers);
	if (*a == NULL)
		return (1);
	return (0);
}

void	free_memory(pthread_t **t, t_phil **p, t_args **a, t_table *table)
{
	int	i;

	i = -1;
	while (++i < (int)table->numbers)
		pthread_detach((*t)[i]);
	free(*t);
	free(*p);
	free(*a);
	free(table->forks);
}
