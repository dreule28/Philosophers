/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreule <dreule@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:44:02 by dreule            #+#    #+#             */
/*   Updated: 2025/05/13 19:24:27 by dreule           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//Includes -- BEGIN
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
//Includes -- END
typedef struct s_shared
{
	int				nb_of_philos;
	int				nb_of_meals;
	int				philos_done_eating;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			sim_start;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	status_mutex;
	bool			sim_stop;
	pthread_mutex_t	*fork_mutexes;
	struct s_philo	*philosophers;
	pthread_t		monitor;
}	t_shared;

typedef struct s_philo
{
	int				philo_id;
	int				times_eaten;
	time_t			time_last_meal;
	pthread_t		thread;
	struct s_shared	*data;
}	t_philo;

//Functions -- BEGIN

//create_threads.c -- BEGIN
void	failed_dining(t_shared *data, int *i);
void	create_and_join_monitor(t_shared *data);
void	create_threads(t_shared *data);
// create_threads.c -- END

//dining_routine.c -- BEGIN
void	handle_initial_timing(t_shared *data, t_philo *philo);
bool	philo_cycle(t_shared *data, t_philo *philo, int l_fork, int r_fork);
void	*dining_routine(void *arg);
//dining_routine.c -- END

// eat_meals.c -- BEGIN
void	release_forks(t_shared *data, int left_fork, int right_fork);
int		philo_eats(t_shared *data, t_philo *philo);
// eat_meals.c -- END

//free_table.c -- BEGIN
void	clear_up_table(t_shared *data);
void	cleanup_threads(t_shared *data, int count);
//free_table.c -- END

//init_table.c -- BEGIN
t_philo	*init_philos(t_shared *data);
bool	init_fork_mutexes(pthread_mutex_t *fork);
bool	init_forks(t_shared *data);
t_philo	*set_table(t_shared *data);
//init_table.c -- END

//main.c -- BEGIN
bool	is_not_nb(char *argv);
int		init_args(char **argv, t_shared *data);
bool	check_args_and_init(char **argv, t_shared *data);
//main.c -- END

//monitor.c -- BEGIN
bool	has_eaten_enough(t_shared *data, int philo_index);
bool	check_philosopher_death(t_shared *data, int philo_i);
bool	all_philosophers_done_eating(t_shared *data, int done_count);
void	set_simulation_stop(t_shared *data);
void	*monitor_routine(void *arg);
//monitor.c -- END

//pick_forks.c -- BEGIN
void	delay_start(t_philo *philo);
bool	try_to_take_fork(t_shared *data, t_philo *philo, int fork_id);
bool	take_second_fork(t_shared *data, t_philo *philo, int f_fork,
			int s_fork);
int		chose_forks(t_shared *data, t_philo *philo, int left_fork,
			int right_fork);
//pick_forks.c -- END

//utils.c -- BEGIN
int		ft_atoi(const char *str);
int		ft_strlen(char *str);
void	error_init(char *str);
time_t	get_time_ms(void);
void	correct_usage(void);
//utils.c -- END

//utils2.c -- BEGIN
void	log_action(t_shared *data, int philo_id, char *log_message);
void	handle_one_philosopher(t_shared *data, t_philo *philo, int left_fork);
bool	simulation_stopped(t_shared *data);
void	custom_sleep(t_shared *data, long duration_in_ms);
int		philo_sleeps(t_shared *data, t_philo *philo);
//utils2.c -- END

//Functions -- END

#endif