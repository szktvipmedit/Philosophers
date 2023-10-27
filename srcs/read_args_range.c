/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args_range.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:31:24 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/23 16:34:39 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	arg_range_check(char **argv, int i)
{
	if (atos(argv[i]) == 0 || atos(argv[i]) > INT_MAX)
		return (write(STDERR, INVALID_NUM_OF_PHILO, INVALID_NUM_OF_PHILO_WC),
			ARG_ERROR);
	return (NEXT_STEP);
}

int	args_range_check(int argc, char **argv)
{
	if (arg_range_check(argv, 1))
		return (ARG_ERROR);
	if (arg_range_check(argv, 2))
		return (ARG_ERROR);
	if (arg_range_check(argv, 3))
		return (ARG_ERROR);
	if (arg_range_check(argv, 4))
		return (ARG_ERROR);
	if (argc == TRUE_ARG_CNT_OPTION)
	{
		if (arg_range_check(argv, 5))
			return (ARG_ERROR);
	}
	return (NEXT_STEP);
}
