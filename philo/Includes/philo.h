/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreule <dreule@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:44:02 by dreule            #+#    #+#             */
/*   Updated: 2025/02/24 14:57:08 by dreule           ###   ########.fr       */
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
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			sim_start;
	pthread_mutex_t	log_mutex;
	bool			sim_stop;
	pthread_mutex_t	*fork_mutexes;
	struct s_philo	*philosophers;
}	t_shared;

typedef struct s_philo
{
	int				philo_id;
	int				times_eaten;
	time_t			time_last_meal;
	pthread_t		thread_id;
	struct s_shared	*data;
}	t_philo;

//Functions -- BEGIN
bool	check_args_and_init(char **argv, t_shared *data);
bool	is_not_nb(char *argv);
int		ft_atoi(const char *str);
void	error_init(char *str);
int		ft_strlen(char *str);
time_t	get_time_ms(void);
t_philo	*set_table(t_shared *data);
void	get_right_fork(t_philo *table, int nb_of_philos);
t_philo	*place_chair_at_table(t_philo *new_chair,
			t_philo *table, t_philo *last);
t_philo	*add_chair(t_shared *data, int i);
//Functions -- END

#endif