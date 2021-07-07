#include "philo.h"

int	monitoring(t_phil *phils, t_table *table)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < table->numbers)
		{
			if (table->to_die < time_now(phils[i].time) - phils[i].last_eat)
			{
				pthread_mutex_lock(&table->print);
				printf("%ld %ld died\n", time_now(phils[i].time),
					phils[i].name + 1);
				return (1);
			}
			if (table->count_to_eat % (table->must_to_eat * table->numbers) == 0
				&& table->count_to_eat != 0)
			{
				pthread_mutex_lock(&table->print);
				printf("dinner is end\n");
				return (1);
			}
			usleep(50);
		}
	}
	return (0);
}

void	take_forks(t_table *table, t_phil *phil)
{
	pthread_mutex_lock(&table->forks[phil->left_fork]);
	pthread_mutex_lock(&table->print);
	printf("%ld %ld has taken a fork\n", time_now(phil->time), phil->name + 1);
	pthread_mutex_unlock(&table->print);
	pthread_mutex_lock(&table->forks[phil->right_fork]);
	pthread_mutex_lock(&table->print);
	phil->last_eat = time_now(phil->time);
	++table->count_to_eat;
	printf("%ld %ld has taken a fork\n", time_now(phil->time), phil->name + 1);
	printf("%ld %ld is eating\n", time_now(phil->time), phil->name + 1);
	pthread_mutex_unlock(&table->print);
	my_usleep(table->to_eat, phil->time);
	pthread_mutex_unlock(&table->forks[phil->left_fork]);
	pthread_mutex_unlock(&table->forks[phil->right_fork]);
}

void	*eat(void *args)
{
	t_args	*arg;
	t_phil	*phil;
	t_table	*table;

	arg = (t_args *)args;
	phil = arg->philosopher;
	table = arg->table;
	if (phil->name % 2 != 0)
		usleep(100);
	while (1)
	{
		take_forks(table, phil);
		pthread_mutex_lock(&table->print);
		printf("%ld %ld is sleeping\n", time_now(phil->time), phil->name + 1);
		pthread_mutex_unlock(&table->print);
		my_usleep(table->to_sleep, phil->time);
		pthread_mutex_lock(&table->print);
		printf("%ld %ld is thinking\n", time_now(phil->time), phil->name + 1);
		pthread_mutex_unlock(&table->print);
	}
	return (NULL);
}

void	start_dinner(t_table *table)
{
	pthread_t	*threads;
	t_phil		*phils;
	t_args		*arguments;
	size_t		i;

	get_memory(&threads, &phils, &arguments, table);
	init_table(table);
	inits_philosophers(phils, table->numbers);
	i = -1;
	while (++i < table->numbers)
	{
		arguments[i].philosopher = &phils[i];
		arguments[i].table = table;
	}
	i = -1;
	while (++i < table->numbers)
	{
		gettimeofday(&phils[i].time, NULL);
		phils[i].last_eat = 0;
		pthread_create(&threads[i], NULL, eat, &arguments[i]);
	}
	monitoring(phils, table);
	free_memory(&threads, &phils, &arguments, table);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc >= 5 && argc <= 6)
	{
		if (read_arguments(&table, argv))
		{
			printf("Erorr input\n");
			return (0);
		}
		start_dinner(&table);
	}
	else
		printf("Erorr input\n");
	return (0);
}
