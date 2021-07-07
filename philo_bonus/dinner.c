#include "philo.h"

void	*check_eats(void *args)
{
	t_args	*arg;
	t_table	*table;
	t_phil	*phil;
	int		i;

	arg = (t_args *)args;
	table = arg->table;
	if (table->must_to_eat == -1)
		return (NULL);
	phil = arg->philosopher;
	i = -1;
	while (++i < (int)table->numbers)
		sem_wait(phil[i].sem_eats);
	sem_wait(table->sem_print);
	printf("dinner is ends\n");
	exit (0);
	return (NULL);
}

void	*check_death(void *args)
{
	t_args	*arg;
	t_phil	*phil;
	t_table	*table;

	arg = (t_args *)args;
	phil = arg->philosopher;
	table = arg->table;
	while (1)
	{
		if (table->to_die < time_now(phil->time) - phil->last_eat)
		{
			sem_wait(table->sem_print);
			printf(RED "%ld %ld died\n", time_now(phil->time), phil->name);
			sem_post(table->sem_death);
		}
	}
	return (NULL);
}

void	take_forks(t_table *table, t_phil *phil)
{
	sem_wait(table->sem_forks);
	sem_wait(table->sem_print);
	printf("%ld %ld has taken a fork\n", time_now(phil->time), phil->name);
	sem_post(table->sem_print);
	sem_wait(table->sem_forks);
	sem_wait(table->sem_print);
	printf("%ld %ld has taken a fork\n", time_now(phil->time), phil->name);
	printf("%ld %ld is eating\n", time_now(phil->time), phil->name);
	phil->eats++;
	if (phil->eats == table->must_to_eat)
		sem_post(phil->sem_eats);
	phil->last_eat = time_now(phil->time);
	++table->count_to_eat;
	sem_post(table->sem_print);
	my_usleep(table->to_eat, phil->time);
	sem_post(table->sem_forks);
	sem_post(table->sem_forks);
}

void	*eat(t_table *table, t_phil *phil)
{
	pthread_t	check;
	t_args		args;

	args.philosopher = phil;
	args.table = table;
	pthread_create(&check, NULL, check_death, &args);
	if (phil->name % 2 == 1)
		usleep(150);
	while (1)
	{
		take_forks(table, phil);
		sem_wait(table->sem_print);
		printf("%ld %ld is sleeping\n", time_now(phil->time), phil->name);
		sem_post(table->sem_print);
		my_usleep(table->to_sleep, phil->time);
		sem_wait(table->sem_print);
		printf("%ld %ld is thinking\n", time_now(phil->time), phil->name);
		sem_post(table->sem_print);
	}
	return (NULL);
}

int	start_dinner(t_table *table)
{
	int			pid;
	size_t		i;
	t_phil		*phil;
	pthread_t	check;
	t_args		arg;

	if (init_table(table, &phil))
		return (1);
	i = -1;
	arg.philosopher = phil;
	arg.table = table;
	while (++i < table->numbers)
	{
		pid = fork();
		if (pid < 0)
			exit (2);
		if (pid == 0)
		{
			eat(table, &phil[i]);
			exit(1);
		}
	}
	pthread_create(&check, NULL, check_eats, &arg);
	sem_wait(table->sem_death);
	exit (0);
}
