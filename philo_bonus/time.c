#include "philo.h"

long	time_now(struct timeval time1)
{
	struct timeval	time2;
	struct timeval	difference;

	gettimeofday(&time2, NULL);
	difference.tv_sec = time2.tv_sec - time1.tv_sec;
	difference.tv_usec = time2.tv_usec - time1.tv_usec;
	if (difference.tv_usec < 0)
	{
		--difference.tv_sec;
		difference.tv_usec += 1000000;
	}
	return (difference.tv_sec * 1000 + difference.tv_usec / 1000);
}

void	my_usleep(long time, struct timeval now)
{
	long long	cur_time;

	cur_time = time_now(now);
	while (1)
	{
		usleep(100);
		if (time_now(now) == cur_time + time)
			break ;
	}
}
