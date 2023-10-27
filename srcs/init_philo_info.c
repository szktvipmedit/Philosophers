/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:02:59 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/25 16:43:33 by kousuzuk         ###   ########.fr       */
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

void	init_philo_info(t_info *info, t_philo_info *philo_info, int i)
{
	pthread_t	th;

	th = NULL;
	philo_info->th = th;
	philo_info->id = i + 1;
	philo_info->info = info;
	philo_info->last_eat_time = get_curr_time();
	philo_info->is_die = 0;
	philo_info->eat_cnt = 0;
	forkid_init(info->philo_info[i]);
}

int	create_philo_info(t_info *info)
{
	size_t	i;

	i = 0;
	info->philo_info = malloc(sizeof(t_philo_info *) * info->num_of_philo);
	if (!info->philo_info)
		return (MALLOC_ERROR);
	while (i < info->num_of_philo)
	{
		info->philo_info[i] = malloc(sizeof(t_philo_info));
		if (!info->philo_info[i])
			return (failed_on_the_way_free_philo_info(info, i), MALLOC_ERROR);
		i++;
	}
	i = 0;
	while (i < info->num_of_philo)
	{
		init_philo_info(info, info->philo_info[i], i);
		i++;
	}
	return (0);
}
