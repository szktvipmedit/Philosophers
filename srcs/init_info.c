/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:14:33 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/25 16:38:09 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	create_forks(t_info *info)
{
	size_t			i;
	info->mutex_forks = malloc(sizeof(pthread_mutex_t) * info->num_of_philo);
	if (!info->mutex_forks)
	{
		write(2, FAILED_MALLOC, FAILED_MALLOC_CC);
		return (MALLOC_ERROR);
	}
	info->forks = malloc(sizeof(bool) * info->num_of_philo);
	if (!info->forks)
	{
		write(2, FAILED_MALLOC, FAILED_MALLOC_CC);
		return (MALLOC_ERROR);
	}
	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_mutex_t	fork;
		if (pthread_mutex_init(&fork, NULL) != 0)
		{
			free_philo_info(info);
			write(2, FAILED_MUTEX_INIT, FAILED_MUTEX_INIT_CC);
			return (MUTEX_ERROR);
		}
		info->mutex_forks[i] = fork;
		info->forks[i] = false;
		i++;
	}
	return (0);
}

void	store_info_arg_values(t_info *info, int argc, char **argv)
{
	info->num_of_philo = atos(argv[1]);
	info->time_to_die = atos(argv[2]);
	info->time_to_eat = atos(argv[3]);
	info->time_to_sleep = atos(argv[4]);
	if (argc == TRUE_ARG_CNT_OPTION)
	{
		info->num_of_each_philo_must_eat = atos(argv[5]);
		info->is_must_eat_option = 1;
	}
	else
	{
		info->num_of_each_philo_must_eat = 1;
		info->is_must_eat_option = 0;
	}
}

int init_each_philo_info_mutexes(t_info *info)
{
	size_t i;
	i = 0;
	while(i < info->num_of_philo)
	{
		pthread_mutex_t	mutex_last_eat_time;
		if(pthread_mutex_init(&mutex_last_eat_time, NULL) != 0)
			return (MUTEX_ERROR);
		info->philo_info[i]->mutex_last_eat_time = mutex_last_eat_time;
		i++;
	}
	return 0;
}

int	init_info_mutexes(t_info *info)
{
	pthread_mutex_t	report_die_to_observer;
	pthread_mutex_t	message_output_auth;
	pthread_mutex_t			mutex_is_all_thread_create;

	if (pthread_mutex_init(&report_die_to_observer, NULL) != 0)
		return (mutex_error(info), MUTEX_ERROR);
	info->report_die_to_observer = report_die_to_observer;
	if (pthread_mutex_init(&message_output_auth, NULL) != 0)
		return (mutex_error(info), MUTEX_ERROR);
	info->message_output_auth = message_output_auth;
	if (pthread_mutex_init(&mutex_is_all_thread_create, NULL) != 0)
		return (mutex_error(info), MUTEX_ERROR);
	info->mutex_is_all_thread_create = mutex_is_all_thread_create;
	if(init_each_philo_info_mutexes(info) == MUTEX_ERROR)
		return (mutex_error(info), MUTEX_ERROR);
	return (0);
}

int	init_info(t_info *info, int argc, char **argv)
{
	store_info_arg_values(info, argc, argv);
	if (create_philo_info(info))
	{
		free_philo_info(info);
		write(2, FAILED_MALLOC, FAILED_MALLOC_CC);
		return (MALLOC_ERROR);
	}
	if (create_forks(info) || init_info_mutexes(info))
		return (MUTEX_ERROR);
	info->start_time = get_curr_time();
	info->is_someone_die = 0;
	info->is_all_thread_create = false;
	return (0);
}
