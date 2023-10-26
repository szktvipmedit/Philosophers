/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:14:28 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/25 15:56:47 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	forkid_init(t_philo_info *philo_info)
{
	philo_info->fork1_id = philo_info->id - 1;
	if (philo_info->id == philo_info->info->num_of_philo
		&& philo_info->info->num_of_philo != 1)
		philo_info->fork2_id = 0;
	else
		philo_info->fork2_id = philo_info->id;
}
int check_eat_cnt_range(t_philo_info *philo_info)
{
	pthread_mutex_lock(&philo_info->mutex_eat_cnt);
	while(philo_info->info->is_must_eat_option && philo_info->eat_cnt != INT_MAX)
	{
		pthread_mutex_unlock(&philo_info->mutex_eat_cnt);
		return 1;
	}
	pthread_mutex_unlock(&philo_info->mutex_eat_cnt);
	return 0;
}
void	action_eat(t_philo_info *philo_info, int fork1_id, int fork2_id)
{
	take_fork(philo_info, fork1_id, fork2_id);
	output_message_eat(philo_info);
	pthread_mutex_lock(&philo_info->mutex_last_eat_time);
	philo_info->last_eat_time = get_curr_time();
	pthread_mutex_unlock(&philo_info->mutex_last_eat_time);
	if (check_eat_cnt_range(philo_info)){
		pthread_mutex_lock(&philo_info->mutex_eat_cnt);
		philo_info->eat_cnt++;
		pthread_mutex_unlock(&philo_info->mutex_eat_cnt);
	}
	ft_usleep(philo_info->info->time_to_eat);
	put_fork(philo_info, fork1_id, fork2_id);
}

void	action_sleep(t_philo_info *philo_info)
{
	output_message_sleep(philo_info);
	ft_usleep(philo_info->info->time_to_sleep);
}

void	action_think(t_philo_info *philo_info)
{
	output_message_think(philo_info);
}

int check_is_someone_die(t_philo_info *philo_info)
{
	pthread_mutex_lock(&philo_info->info->report_die_to_observer);
	while(!philo_info->info->is_someone_die)
	{
		pthread_mutex_unlock(&philo_info->info->report_die_to_observer);
		return 1;
	}
	pthread_mutex_unlock(&philo_info->info->report_die_to_observer);
	return 0;
}

int	philo_life(t_philo_info *philo_info)
{
	action_think(philo_info);
	if (philo_info->id % 2 == 0)
		ft_usleep(10);
	while (check_is_someone_die(philo_info))
	{
		action_eat(philo_info, philo_info->fork1_id, philo_info->fork2_id);
		action_sleep(philo_info);
		action_think(philo_info);
	}
	return (1);
}
