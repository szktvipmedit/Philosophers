/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:23:36 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/10/25 15:59:18 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

// error_message and word_cound
# define INVALID_NUM_OF_ARG "Error : Invalid number of arguments\n"
# define INVALID_NUM_OF_ARG_WC 36
# define INVALID_VALUE_OF_ARG "Error : Invalid value of arguments\n"
# define INVALID_VALUE_OF_ARG_WC 36
# define INVALID_NUM_OF_PHILO \
	"Error : num_of_philo must be \
less than or equal to INT_MAX\n"
# define INVALID_NUM_OF_PHILO_WC 59
# define FAILED_MUTEX_INIT "Error : Mutex initialization failed\n"
# define FAILED_MUTEX_INIT_WC 36
# define FAILED_PTHREAD_CREATE "Error : Pthread initialization failed\n"
# define FAILED_PTHREAD_CREATE_WC 38
# define FAILED_PTHREAD_JOIN "Error : Pthread join failed\n"
# define FAILED_PTHREAD_JOIN_WC 28
# define FAILED_MALLOC "Error : malloc failed\n"
# define FAILED_MALLOC_WC 22
// utils
# define STDERR 2
# define NEXT_STEP 0
# define CONTINUE_LOOP 0
# define STOP_PHILO_LIFE 1
# define SUCCESS 1
# define EXIT 0
// arg
# define TRUE_ARG_CNT_DEFAULT 5
# define TRUE_ARG_CNT_OPTION 6
// error
# define ARG_ERROR 1
# define MUTEX_ERROR 1
# define PTHREAD_ERROR 1
# define MALLOC_ERROR 1
# define JOIN_ERROR 1

struct	s_info;

typedef struct s_philo_info
{
	struct s_info	*info;
	pthread_t		th;
	size_t			id;
	size_t			eat_cnt;
	pthread_mutex_t	mutex_eat_cnt;
	size_t			is_die;
	size_t			last_eat_time;
	pthread_mutex_t	mutex_last_eat_time;

	int				fork1_id;
	int				fork2_id;
}					t_philo_info;

typedef struct s_info
{
	size_t			num_of_philo;
	size_t			num_of_each_philo_must_eat;
	int				is_someone_die;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	bool			is_must_eat_option;
	size_t			must_eat_philo_cnt;

	size_t			start_time;

	pthread_mutex_t	report_die_to_observer;
	bool			*forks;
	pthread_mutex_t	*mutex_forks;
	pthread_mutex_t	message_output_auth;
	bool			all_thread_finished;
	pthread_mutex_t	mutex_all_thread_finished;
	t_philo_info	**philo_info;
}					t_info;

// libft_utils
size_t				ft_strlen(const char *s);
int					ft_isdigit(int i);
size_t				atos(char *str);
size_t				get_curr_time(void);
void				ft_usleep(size_t ms);

// read_args.c
int					not_admit_minus_or_char(int i, char **argv);
int					input_value_check(int argc, char **argv);
int					arg_error_check(int argc, char **argv);
int					read_input(t_info *info, int argc, char **argv);

// read_args_range.c
int					arg_range_check(char **argv, int i);
int					args_range_check(int argc, char **argv);

// init_info.c
void				store_info_arg_values(t_info *info, int argc, char **argv);
int					init_info_mutexes(t_info *info);
int					init_info(t_info *info, int argc, char **argv);

//init_info_create_forks.c
int					store_forks(t_info *info);
int					create_forks(t_info *info);

// init_philo_info.c
void				forkid_init(t_philo_info *philo_info);
void				init_philo_info(t_info *info, t_philo_info *philo_info,
						int i);
int					create_philo_info(t_info *info);

// create_threads.c
int					all_philo_create(t_info *info);
int					all_philo_join(t_info *info);
int					create_observer(t_info *info, pthread_t *observer);
int					create_philo(t_info *info);
int					create_threads(t_info *info);

// threads.c
void				observer_philo_survive(t_info *info);
int					philo_life(t_philo_info *philo_info);

// thread_observer_utils.c
void				stop_philo_life_by_edit_is_someone_die(t_info *info);
int					check_die_in_observer(t_info *info);
void				count_must_eat_philo(t_info *info,
						size_t *must_eat_philo_cnt);
void				count_must_eat_philo(t_info *info,
						size_t *must_eat_philo_cnt);
int					check_must_eat_in_observer(t_info *info);

// actions.c
void				update_last_eat_time(t_philo_info *philo_info);
void				action_eat(t_philo_info *philo_info, int fork1_id,
						int fork2_id);
void				action_sleep(t_philo_info *philo_info);
void				action_think(t_philo_info *philo_info);

// actions_fork.c
void				get_fork1(t_philo_info *philo_info, int fork1_id);
void				get_fork2(t_philo_info *philo_info, int fork2_id);
void				take_fork(t_philo_info *philo_info, int fork1_id,
						int fork2_id);
void				put_fork(t_philo_info *philo_info, int fork1_id,
						int fork2_id);

// actions_output_message.c
void				output_message_get_fork(t_philo_info *philo_info);
void				output_message_eat(t_philo_info *philo_info);
void				output_message_sleep(t_philo_info *philo_info);
void				output_message_think(t_philo_info *philo_info);
void				output_message_die(t_info *info);

// mutex_check.c
int					check_is_someone_die(t_philo_info *philo_info);
int					check_eat_cnt_need(t_philo_info *philo_info);
int					check_eat_cnt(t_philo_info *philo_info);
int					check_all_thread_finished(t_info *info);
int					check_die_by_time(t_philo_info *philo_info);

// main.c
void				clean_all_values(t_info *info);
void				clean_forks(t_info *info);
void				free_philo_info(t_info *info);
void				failed_on_the_way_free_philo_info(t_info *info, int i);

// clean_utils.c
void    mutex_destroy(pthread_mutex_t *ptr);
void				failed_on_the_way_free_philo_info(t_info *info, int i);
void				failed_on_the_way_mutex_forks_destroy(t_info *info, int i);
void				failed_on_the_way_each_philo_info_mutex_destroy(
						t_info *info, int i, int is_eat_cnt);

#endif
