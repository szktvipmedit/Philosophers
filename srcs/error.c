/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:28:07 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/23 15:29:48 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_error(t_info *info)
{
	free_philo_info(info);
	write(2, FAILED_MUTEX_INIT, FAILED_MUTEX_INIT_CC);
}
