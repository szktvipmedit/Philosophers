#include "../incs/philo.h"

void	stop_philo_life_by_edit_is_someone_die(t_info *info)
{
	pthread_mutex_lock(&info->report_die_to_observer);
	info->is_someone_die = 1;
	pthread_mutex_unlock(&info->report_die_to_observer);
}

int	check_die_in_observer(t_info *info)
{
	size_t	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		if (check_die_by_time(info->philo_info[i]))
		{
			stop_philo_life_by_edit_is_someone_die(info);
			output_message_die(info);
			return (STOP_PHILO_LIFE);
		}
		i++;
	}
	return (CONTINUE_LOOP);
}

void	count_must_eat_philo(t_info *info, size_t *must_eat_philo_cnt)
{
	size_t	i;

	i = 0;
	(void)must_eat_philo_cnt;
	while (i < info->num_of_philo)
	{
		if (check_eat_cnt(info->philo_info[i++]))
			(*must_eat_philo_cnt)++;
		else
			break ;
	}
}

int	check_must_eat_in_observer(t_info *info)
{
	size_t	must_eat_philo_cnt;

	must_eat_philo_cnt = 0;
	count_must_eat_philo(info, &must_eat_philo_cnt);
	if (must_eat_philo_cnt == info->num_of_philo)
	{
		stop_philo_life_by_edit_is_someone_die(info);
		return (STOP_PHILO_LIFE);
	}
	return (CONTINUE_LOOP);
}
