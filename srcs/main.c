/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:14:35 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/25 11:19:49 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	clean_forks(t_info *info)
{
	int	i;

	i = info->num_of_philo - 1;
	while (0 <= i)
	{
		pthread_mutex_destroy(&info->mutex_forks[i]);
		i--;
	}
	free(info->mutex_forks);
	free(info->forks);
}

void	clean_all_values(t_info *info)
{
	int	i;

	i = info->num_of_philo - 1;
	while (0 <= i)
	{
		pthread_mutex_destroy(&info->philo_info[i]->mutex_eat_cnt);
		pthread_mutex_destroy(&info->philo_info[i]->mutex_last_eat_time);
		pthread_mutex_destroy(&info->mutex_forks[i]);
		free(info->philo_info[i]);
		i--;
	}
	pthread_mutex_destroy(&info->report_die_to_observer);
	pthread_mutex_destroy(&info->message_output_auth);
	pthread_mutex_destroy(&info->mutex_all_thread_finished);
	free(info->philo_info);
	free(info->mutex_forks);
	free(info->forks);
	free(info);
}

void	free_philo_info(t_info *info)
{
	int	i;

	i = info->num_of_philo - 1;
	while (0 <= i)
	{
		free(info->philo_info[i]);
		i--;
	}
	free(info->philo_info);
}

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q philo");
// }

// freeやdestroyは確定する時の最下層で行う
int	main(int argc, char **argv)
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
		return (write(STDERR, FAILED_MALLOC, FAILED_MALLOC_WC), EXIT);
	if (read_input(info, argc, argv))
		return (free(info), EXIT);
	if (create_threads(info))
		return (clean_all_values(info), EXIT);
	clean_all_values(info);
	return (SUCCESS);
}
