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
	free(info->mutex_forks);
	free(info);
}

void	failed_on_the_way_free_philo_info(t_info *info, int i)
{
	--i;
	while (i >= 0)
	{
		free(info->philo_info[i]);
		i--;
	}
	free(info);
}

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q philo");
// }

int	main(int argc, char **argv)
{
	t_info		*info;
	pthread_t	observer;

	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
	{
		write(2, FAILED_MALLOC, FAILED_MALLOC_CC);
		return (0);
	}
	if (read_input(info, argc, argv))
		return (0);
	if (pthread_create(&observer, NULL, (void *)observer_philo_survive,
			(void *)info))
	{
		free_philo_info(info);
		write(2, FAILED_PTHREAD_CREATE, FAILED_PTHREAD_CREATE_CC);
		return (PTHREAD_ERROR);
	}
	if (create_threads(info))
		return (0);
	pthread_join(observer, NULL);
	free_philo_info(info);
	return (0);
}
