/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:14:40 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/23 17:01:12 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	check_die(t_info *info)
{
	size_t	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		if (get_curr_time()
			- info->philo_info[i]->last_eat_time > info->time_to_die)
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

int	check_must_eat(t_info *info)
{
	size_t	i;
	size_t	must_eat_philo_cnt;

	i = 0;
	must_eat_philo_cnt = 0;
	while (i < info->num_of_philo)
	{
		if (info->philo_info[i++]->eat_cnt == info->num_of_each_philo_must_eat)
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

void	observer_philo_survive(t_info *info)
{
	int				i;

	i = 0;
	while (1)
	{
		if (check_die(info) || check_must_eat(info))
			break ;
	}
	while (!info->is_all_thread_create)
		(void)i;
}
