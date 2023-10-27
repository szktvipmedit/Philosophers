/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:14:30 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/25 15:58:52 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	all_philo_create(t_info *info)
{
	size_t	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		if (pthread_create(&info->philo_info[i]->th, NULL, (void *)philo_life,
				(void *)info->philo_info[i]))
		{
			free_philo_info(info);
			return (write(STDERR, FAILED_PTHREAD_CREATE,
					FAILED_PTHREAD_CREATE_WC), PTHREAD_ERROR);
		}
		i++;
	}
	return (NEXT_STEP);
}

int	all_philo_join(t_info *info)
{
	size_t	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		if (pthread_join(info->philo_info[i++]->th, NULL) != 0)
			return (write(STDERR, FAILED_PTHREAD_JOIN, FAILED_PTHREAD_JOIN_WC),
				JOIN_ERROR);
	}
	return (NEXT_STEP);
}

int	create_philo(t_info *info)
{
	if (all_philo_create(info))
	{
		free_philo_info(info);
		return (PTHREAD_ERROR);
	}
	if (all_philo_join(info))
	{
		free_philo_info(info);
		return (JOIN_ERROR);
	}
	pthread_mutex_lock(&info->mutex_all_thread_finished);
	info->all_thread_finished = true;
	pthread_mutex_unlock(&info->mutex_all_thread_finished);
	return (NEXT_STEP);
}

int	create_observer(t_info *info, pthread_t *observer)
{
	if (pthread_create(observer, NULL, (void *)observer_philo_survive,
			(void *)info))
	{
		free_philo_info(info);
		return (write(STDERR, FAILED_PTHREAD_CREATE, FAILED_PTHREAD_CREATE_WC),
			PTHREAD_ERROR);
	}
	return (NEXT_STEP);
}

int	create_threads(t_info *info)
{
	pthread_t	observer;

	if (create_observer(info, &observer))
		return (PTHREAD_ERROR);
	if (create_philo(info))
		return (PTHREAD_ERROR);
	pthread_join(observer, NULL);
	return (NEXT_STEP);
}
