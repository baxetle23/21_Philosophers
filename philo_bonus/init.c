#include "philo.h"

int	init_table(t_table *table, t_phil **phil)
{
	int	i;

	sem_unlink("sem_print");
	sem_unlink("sem_death");
	sem_unlink("sem_forks");
	sem_unlink("eats");
	table->sem_print = sem_open("sem_print", O_CREAT, 0777, 1);
	table->sem_death = sem_open("sem_death", O_CREAT, 0777, 0);
	table->sem_forks = sem_open("sem_forks", O_CREAT, 0777, table->numbers);
	if (table->sem_forks == SEM_FAILED || table->sem_death == SEM_FAILED
		|| table->sem_print == SEM_FAILED)
		return (1);
	*phil = (t_phil *)malloc(sizeof(t_phil) * table->numbers);
	i = -1;
	while (++i < (int)table->numbers)
	{
		(*phil)[i].sem_eats = sem_open("eats", O_CREAT, 0777, 0);
		(*phil)[i].name = i + 1;
		(*phil)[i].last_eat = 0;
		(*phil)[i].eats = 0;
		gettimeofday(&((*phil)[i].time), NULL);
	}
	return (0);
}
