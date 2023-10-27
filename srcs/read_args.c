/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:14:38 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/23 16:34:07 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	not_admit_minus_or_char(int i, char **argv)
{
	int	j;
	int	each_arg_len;

	j = 0;
	each_arg_len = ft_strlen(argv[i]);
	if (argv[i][j] == '+')
		j++;
	while (j < each_arg_len)
	{
		if (!('0' <= argv[i][j] && argv[i][j] <= '9'))
			return (ARG_ERROR);
		j++;
	}
	return (NEXT_STEP);
}

int	input_value_check(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (argv[i] == NULL)
			return (ARG_ERROR);
		if (not_admit_minus_or_char(i, argv))
			return (ARG_ERROR);
		i++;
	}
	return (NEXT_STEP);
}

int	arg_error_check(int argc, char **argv)
{
	if (argc != TRUE_ARG_CNT_DEFAULT && argc != TRUE_ARG_CNT_OPTION)
		return (write(STDERR, INVALID_NUM_OF_ARG, INVALID_NUM_OF_ARG_WC),
			ARG_ERROR);
	if (input_value_check(argc, argv))
		return (write(STDERR, INVALID_VALUE_OF_ARG, INVALID_VALUE_OF_ARG_WC),
			ARG_ERROR);
	return (NEXT_STEP);
}

int	read_input(t_info *info, int argc, char **argv)
{
	if (arg_error_check(argc, argv))
		return (ARG_ERROR);
	if (args_range_check(argc, argv))
		return (ARG_ERROR);
	if (init_info(info, argc, argv))
		return (MUTEX_ERROR);
	return (NEXT_STEP);
}
