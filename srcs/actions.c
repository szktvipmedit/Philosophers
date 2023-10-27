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

void update_last_eat_time(t_philo_info *philo_info)
{
	pthread_mutex_lock(&philo_info->mutex_last_eat_time);
	philo_info->last_eat_time = get_curr_time();
	pthread_mutex_unlock(&philo_info->mutex_last_eat_time);
}

void	action_eat(t_philo_info *philo_info, int fork1_id, int fork2_id)
{
	take_fork(philo_info, fork1_id, fork2_id);
	output_message_eat(philo_info);
	update_last_eat_time(philo_info);
	if (check_eat_cnt_need(philo_info)){
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
