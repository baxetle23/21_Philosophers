#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philosopher
{
	size_t			name;
	size_t			left_fork;
	size_t			right_fork;
	size_t			last_eat;
	char			eat;
	struct timeval	time;
}					t_phil;

typedef struct s_table
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	size_t			numbers;
	int				to_die;
	int				to_eat;
	int				to_sleep;
	int				must_to_eat;
	size_t			count_to_eat;
	long long		time;
}					t_table;

typedef struct s_args
{
	t_phil	*philosopher;
	t_table	*table;
}	t_args;

int		read_arguments(t_table *table, char **argv);
int		inits_philosophers(t_phil *philosopher, size_t count);
int		init_table(t_table *table);
long	time_now(struct timeval time);
void	my_usleep(long time, struct timeval now);

int		get_memory(pthread_t **t, t_phil **p, t_args **a, t_table *table);
void	free_memory(pthread_t **t, t_phil **p, t_args **a, t_table *table);

#endif