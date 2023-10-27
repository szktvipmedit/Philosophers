#include "../incs/philo.h"

int	check_eat_cnt_need(t_philo_info *philo_info)
{
	pthread_mutex_lock(&philo_info->mutex_eat_cnt);
	while (philo_info->info->is_must_eat_option
		&& philo_info->eat_cnt != INT_MAX)
	{
		pthread_mutex_unlock(&philo_info->mutex_eat_cnt);
		return (1);
	}
	pthread_mutex_unlock(&philo_info->mutex_eat_cnt);
	return (0);
}

int	check_is_someone_die(t_philo_info *philo_info)
{
	pthread_mutex_lock(&philo_info->info->report_die_to_observer);
	while (!philo_info->info->is_someone_die)
	{
		pthread_mutex_unlock(&philo_info->info->report_die_to_observer);
		return (1);
	}
	pthread_mutex_unlock(&philo_info->info->report_die_to_observer);
	return (0);
}

int	check_eat_cnt(t_philo_info *philo_info)
{
	pthread_mutex_lock(&philo_info->mutex_eat_cnt);
	if (philo_info->eat_cnt >= philo_info->info->num_of_each_philo_must_eat)
	{
		pthread_mutex_unlock(&philo_info->mutex_eat_cnt);
		return (1);
	}
	pthread_mutex_unlock(&philo_info->mutex_eat_cnt);
	return (0);
}

int	check_all_thread_finished(t_info *info)
{
	pthread_mutex_lock(&info->mutex_all_thread_finished);
	if (info->all_thread_finished)
	{
		pthread_mutex_unlock(&info->mutex_all_thread_finished);
		return (1);
	}
	pthread_mutex_unlock(&info->mutex_all_thread_finished);
	return (0);
}

int	check_die_by_time(t_philo_info *philo_info)
{
	pthread_mutex_lock(&philo_info->mutex_last_eat_time);
	if (get_curr_time()
		- philo_info->last_eat_time > philo_info->info->time_to_die)
	{
		pthread_mutex_unlock(&philo_info->mutex_last_eat_time);
		return (1);
	}
	pthread_mutex_unlock(&philo_info->mutex_last_eat_time);
	return (0);
}
