/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreule <dreule@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:09:23 by dreule            #+#    #+#             */
/*   Updated: 2025/02/24 16:53:16 by dreule           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo		*philo;
	t_shared	*data;
	int			left_fork;
	int			right_fork;

	philo = (t_philo *)arg;
	data = philo->data;
	left_fork = philo->philo_id - 1;
	right_fork = philo->philo_id % data->nb_of_philos;
	usleep(1000);
	while (!data->sim_stop)
	{
		//left fork
		pthread_mutex_lock(&data->fork_mutexes[left_fork]);
		pthread_mutex_lock(&data->log_mutex);
		printf("%ld %d has taken a fork\n", get_time_ms() - data->sim_start, philo->philo_id);
		pthread_mutex_unlock(&data->log_mutex);
		//right fork
		pthread_mutex_lock(&data->fork_mutexes[right_fork]);
		pthread_mutex_lock(&data->log_mutex);
		printf("%ld %d has taken a fork\n", get_time_ms() - data->sim_start, philo->philo_id);
		pthread_mutex_unlock(&data->log_mutex);
		//eating
		pthread_mutex_lock(&data->log_mutex);
		printf("%ld %d is eating\n", get_time_ms() - data->sim_start, philo->philo_id);
		pthread_mutex_unlock(&data->log_mutex);
		//update last_time
		philo->time_last_meal = get_time_ms();
		philo->times_eaten++;
		usleep(data->time_to_eat * 1000);
		//release forks
		pthread_mutex_unlock(&data->fork_mutexes[left_fork]);
		pthread_mutex_unlock(&data->fork_mutexes[right_fork]);
		//sleeping
		pthread_mutex_lock(&data->log_mutex);
		printf("%ld %d is sleeping\n", get_time_ms() - data->sim_start, philo->philo_id);
		pthread_mutex_unlock(&data->log_mutex);
		usleep(data->time_to_sleep * 1000);
		//thinking
		pthread_mutex_lock(&data->log_mutex);
		printf("%ld %d is thinking\n", get_time_ms() - data->sim_start, philo->philo_id);
		pthread_mutex_unlock(&data->log_mutex);
	}
	return (NULL);
}

void	create_threads(t_shared *data)
{
	int		i;

	i = 0;
	while (i++ < data->nb_of_philos)
	{
		if (pthread_create(&data->philosophers[i].thread, NULL, &routine, (void *)&data->philosophers[i]))
		{
			printf("Error creating threads!");
			cleanup_threads(data, i);
			return ;
		}
	}
	i = 0;
	while (i++ < data->nb_of_philos)
	{
		if (pthread_join(data->philosophers[i].thread, NULL))
		{
			printf("Error joining threads!");
			return ;
		}
	}
}
