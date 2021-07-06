#include "philo.h"

long	ft_atoi(const char *str)
{
	long	nbr;
	int		flag;
	char	*s;

	s = (char *)str;
	nbr = 0;
	flag = 1;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-')
	{
		s++;
		flag = -1;
	}
	else if (*s == '+')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		nbr = nbr * 10 + (*s - '0');
		s++;
	}
	return (nbr * flag);
}

void	read_arguments(t_table *table, char **argv)
{
	table->numbers = ft_atoi(argv[1]);
	table->to_die = ft_atoi(argv[2]);
	table->to_eat = ft_atoi(argv[3]);
	table->to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		table->must_to_eat = ft_atoi(argv[5]);
	else
		table->must_to_eat = -1;
}
