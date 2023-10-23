/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:14:30 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/23 16:59:42 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	create_thread_observer(t_info *info)
{
	pthread_t	observer;

	if (pthread_create(&observer, NULL, (void *)observer_philo_survive,
			(void *)info))
	{
		free_philo_info(info);
		write(2, FAILED_PTHREAD_CREATE, FAILED_PTHREAD_CREATE_CC);
		return (PTHREAD_ERROR);
	}
	return (0);
}

int	create_threads_philo(t_info *info)
{
	size_t	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		if (pthread_create(&info->philo_info[i]->th, NULL, (void *)philo_life,
				(void *)info->philo_info[i]))
		{
			free_philo_info(info);
			write(2, FAILED_PTHREAD_CREATE, FAILED_PTHREAD_CREATE_CC);
			return (PTHREAD_ERROR);
		}
		i++;
	}
	info->is_all_thread_create = 1;
	return (0);
}

int	create_threads(t_info *info)
{
	if (create_threads_philo(info))
		return (PTHREAD_ERROR);
	return (0);
}
