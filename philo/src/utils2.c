/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreule <dreule@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:46:11 by dreule            #+#    #+#             */
/*   Updated: 2025/02/25 13:57:55 by dreule           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_action(t_shared *data, int philo_id, char *log_message)
{
	pthread_mutex_lock(&data->log_mutex);
	if (!data->sim_stop)
		printf("%ld %d %s\n", data->sim_start, philo_id, log_message);
	pthread_mutex_unlock(&data->log_mutex);
}

void	handle_one_philosopher(t_shared *data, t_philo *philo, int left_fork,
								int right_fork)
{
	pthread_mutex_lock(&data->fork_mutexes[left_fork]);
	log_action(data, philo->philo_id, "has taken a fork");
	usleep(data->time_to_die * 1000);
	log_action(data, philo->philo_id, "died");
	pthread_mutex_unlock(&data->fork_mutexes[left_fork]);
	return (NULL);
}
