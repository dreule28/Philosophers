/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreule <dreule@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:44:02 by dreule            #+#    #+#             */
/*   Updated: 2025/02/26 19:03:40 by dreule           ###   ########.fr       */
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

//Parsing -- BEGIN
bool	check_args_and_init(char **argv, t_shared *data);
void	correct_usage(void);
//Parsing -- END

//Utils -- BEGIN
bool	is_not_nb(char *argv);
int		ft_atoi(const char *str);
void	error_init(char *str);
int		ft_strlen(char *str);
time_t	get_time_ms(void);
void	log_action(t_shared *data, int philo_id, char *log_message);
//Utils -- END

//Initing -- BEGIN
t_philo	*set_table(t_shared *data);
bool	init_forks(t_shared *data);
bool	init_fork_mutexes(pthread_mutex_t *fork);
t_philo	*init_philos(t_shared *data);
t_philo	*init_philo(t_shared *data, int id);
//Initing -- END

//Threads -- BEGIN
void	create_threads(t_shared *data);
void	*dining_routine(void *arg);
void	handle_one_philosopher(t_shared *data, t_philo *philo, int left_fork,
								int right_fork);
//Threads -- END

//Cleaning -- BEGIN
void	clear_up_table(t_shared *data);
void	cleanup_threads(t_shared *data, int count);
//Cleaning -- END

//Functions -- END

#endif