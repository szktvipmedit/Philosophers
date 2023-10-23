/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:14:23 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/23 15:14:25 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	get_fork1(t_philo_info *philo_info, int fork1_id)
{
	pthread_mutex_lock(&philo_info->info->forks[fork1_id]);
	output_message_get_fork(philo_info);
}

void	get_fork2(t_philo_info *philo_info, int fork2_id)
{
	pthread_mutex_lock(&philo_info->info->forks[fork2_id]);
	output_message_get_fork(philo_info);
}

void	take_fork(t_philo_info *philo_info, int fork1_id, int fork2_id)
{
	get_fork1(philo_info, fork1_id);
	if (philo_info->info->num_of_philo == 1)
		ft_usleep(philo_info->info->time_to_die * 2);
	get_fork2(philo_info, fork2_id);
}

void	put_fork(t_philo_info *philo_info, int fork1_id, int fork2_id)
{
	pthread_mutex_unlock(&philo_info->info->forks[fork1_id]);
	pthread_mutex_unlock(&philo_info->info->forks[fork2_id]);
}
