#include "philo.h"

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
		if (start_dinner(&table))
		{
			printf("Erorr init\n");
			return (0);
		}
	}
	else
		printf("Erorr input\n");
	return (0);
}
