#include "../incs/philo.h"

int	store_forks(t_info *info)
{
	size_t			i;
	pthread_mutex_t	fork;

	i = 0;
	while (i < info->num_of_philo)
	{
		if (pthread_mutex_init(&fork, NULL) != 0)
		{
			failed_on_the_way_mutex_forks_destroy(info, i);
			return (write(STDERR, FAILED_MUTEX_INIT, FAILED_MUTEX_INIT_WC),
				MUTEX_ERROR);
		}
		info->mutex_forks[i] = fork;
		info->forks[i] = false;
		i++;
	}
	return (NEXT_STEP);
}

int	create_forks(t_info *info)
{
	info->mutex_forks = malloc(sizeof(pthread_mutex_t) * info->num_of_philo);
	if (!info->mutex_forks)
		return (write(STDERR, FAILED_MALLOC, FAILED_MALLOC_WC), MALLOC_ERROR);
	info->forks = malloc(sizeof(bool) * info->num_of_philo);
	if (!info->forks)
	{
		free(info->mutex_forks);
		return (write(STDERR, FAILED_MALLOC, FAILED_MALLOC_WC), MALLOC_ERROR);
	}
	store_forks(info);
	return (NEXT_STEP);
}
