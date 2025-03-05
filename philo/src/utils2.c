/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreule <dreule@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:46:11 by dreule            #+#    #+#             */
/*   Updated: 2025/03/05 17:09:56 by dreule           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_action(t_shared *data, int philo_id, char *log_message)
{
	pthread_mutex_lock(&data->log_mutex);
	if (!data->sim_stop)
		printf("%ld %d %s\n", get_time_ms() - data->sim_start, philo_id,
			log_message);
	pthread_mutex_unlock(&data->log_mutex);
}

void	handle_one_philosopher(t_shared *data, t_philo *philo, int left_fork)
{
	pthread_mutex_lock(&data->fork_mutexes[left_fork]);
	log_action(data, philo->philo_id, "has taken a fork");
	usleep(data->time_to_die * 1000);
	log_action(data, philo->philo_id, "died");
	pthread_mutex_unlock(&data->fork_mutexes[left_fork]);
}

bool	simulation_stopped(t_shared *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	if (data->sim_stop)
	{
		pthread_mutex_unlock(&data->stop_mutex);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(&data->stop_mutex);
		return (false);
	}
}

void	custom_sleep(t_shared *data, long duration_in_ms)
{
	long	start_time;
	long	elapsed_time;

	start_time = get_time_ms();
	elapsed_time = 0;
	while (elapsed_time < duration_in_ms && !simulation_stopped(data))
	{
		usleep(1000);
		elapsed_time = get_time_ms() - start_time;
	}
}

int	philo_sleeps(t_shared *data, t_philo *philo)
{
	log_action(data, philo->philo_id, "is sleeping");
	custom_sleep(data, data->time_to_sleep);
	if (simulation_stopped(data))
		return (0);
	return (1);
}
