#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define RESET   "\x1b[0m"

typedef struct s_philosopher
{
	size_t			name;
	int				last_eat;
	int				eats;
	sem_t			*sem_eats;
	struct timeval	time;
}					t_phil;

typedef struct s_table
{
	sem_t		*sem_print;
	sem_t		*sem_death;
	sem_t		*sem_forks;
	size_t		numbers;
	int			to_die;
	int			to_eat;
	int			to_sleep;
	int			must_to_eat;
	int			count_to_eat;
	long long	time;
}				t_table;

typedef struct s_args
{
	t_phil	*philosopher;
	t_table	*table;
}	t_args;

int		read_arguments(t_table *table, char **argv);
int		start_dinner(t_table *table);
int		inits_philosophers(t_phil *philosopher, size_t count);
int		init_table(t_table *table, t_phil **phil);
long	time_now(struct timeval time);
void	my_usleep(long time, struct timeval now);

#endif