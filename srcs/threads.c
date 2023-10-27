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

void	observer_philo_survive(t_info *info)
{
	while (1)
	{
		if (check_die_in_observer(info) || check_must_eat_in_observer(info))
			break ;
	}
	if (check_all_thread_finished(info))
		return ;
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
	return (EXIT);
}
