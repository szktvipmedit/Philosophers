/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:14:40 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/25 16:03:00 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int check_die_by_time(t_philo_info *philo_info)
{
	
	pthread_mutex_lock(&philo_info->mutex_last_eat_time);
	if(get_curr_time() - philo_info->last_eat_time > philo_info->info->time_to_die)
	{
		pthread_mutex_unlock(&philo_info->mutex_last_eat_time);
		return 1;
	}
	pthread_mutex_unlock(&philo_info->mutex_last_eat_time);
	return 0; 
}

int	check_die(t_info *info)
{
	size_t	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		if (check_die_by_time(info->philo_info[i]))
		{
			pthread_mutex_lock(&info->report_die_to_observer);
			info->is_someone_die = info->philo_info[i]->id;
			output_message_die(info);
			pthread_mutex_unlock(&info->report_die_to_observer);
			return (1);
		}
		i++;
	}
	return (0);
}

int check_eat_cnt(t_philo_info *philo_info)
{
	pthread_mutex_lock(&philo_info->mutex_eat_cnt);
	if(philo_info->eat_cnt == philo_info->info->num_of_each_philo_must_eat)
	{
		pthread_mutex_unlock(&philo_info->mutex_eat_cnt);
		return 1;
	}
	pthread_mutex_unlock(&philo_info->mutex_eat_cnt);
	return 0;
}

int	check_must_eat(t_info *info)
{
	size_t	i;
	size_t	must_eat_philo_cnt;

	i = 0;
	must_eat_philo_cnt = 0;
	while (i < info->num_of_philo)
	{
		if (check_eat_cnt(info->philo_info[i++]))
			must_eat_philo_cnt++;
	}
	if (must_eat_philo_cnt == info->num_of_philo)
	{
		pthread_mutex_lock(&info->report_die_to_observer);
		info->is_someone_die = 1;
		pthread_mutex_unlock(&info->report_die_to_observer);
		return (1);
	}
	return (0);
}

int loop_all_thread_create(t_info *info)
{
	pthread_mutex_lock(&info->mutex_is_all_thread_create);
	if(!info->is_all_thread_create)
	{
		pthread_mutex_unlock(&info->mutex_is_all_thread_create);
		return 1;
	}
	pthread_mutex_unlock(&info->mutex_is_all_thread_create);
	return 0;
}

void	observer_philo_survive(t_info *info)
{
	while (1)
	{
		if (check_die(info) || check_must_eat(info))
			break ;
	};
}
