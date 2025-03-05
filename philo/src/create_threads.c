/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreule <dreule@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:09:23 by dreule            #+#    #+#             */
/*   Updated: 2025/03/05 16:15:19 by dreule           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	chose_forks(t_shared *data, t_philo *philo, int left_fork, int right_fork)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(&data->fork_mutexes[right_fork]);
		log_action(data, philo->philo_id, "has taken a fork");
		if (simulation_stopped(data))
		{
			pthread_mutex_unlock(&data->fork_mutexes[right_fork]);
			return (0);
		}
		pthread_mutex_lock(&data->fork_mutexes[left_fork]);
		log_action(data, philo->philo_id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&data->fork_mutexes[left_fork]);
		log_action(data, philo->philo_id, "has taken a fork");
		if (simulation_stopped(data))
		{
			pthread_mutex_unlock(&data->fork_mutexes[left_fork]);
			return (0);
		}
		pthread_mutex_lock(&data->fork_mutexes[right_fork]);
		log_action(data, philo->philo_id, "has taken a fork");
	}
	return (1);
}

int	philo_eats(t_shared *data, t_philo *philo)
{
	log_action(data, philo->philo_id, "is eating");
	philo->time_last_meal = get_time_ms();
	philo->times_eaten++;
	pthread_mutex_lock(&data->stop_mutex);
	if (data->nb_of_meals > 0 && philo->times_eaten >= data->nb_of_meals)
	{
		data->philos_done_eating++;
		if (data->philos_done_eating >= data->nb_of_philos)
			data->sim_stop = 1;
	}
	pthread_mutex_unlock(&data->stop_mutex);
	custom_sleep(data, 1);
	if (simulation_stopped(data))
		return (0);
	return (1);
}

void	release_forks(t_shared *data, int left_fork, int right_fork)
{
	pthread_mutex_unlock(&data->fork_mutexes[left_fork]);
	pthread_mutex_unlock(&data->fork_mutexes[right_fork]);
}

void	*dining_routine(void *arg)
{
	t_philo		*philo;
	t_shared	*data;
	int			left_fork;
	int			right_fork;

	philo = (t_philo *)arg;
	data = philo->data;
	left_fork = philo->philo_id - 1;
	right_fork = philo->philo_id % data->nb_of_philos;
	// usleep(philo->philo_id * 1000);
	if (data->nb_of_philos == 1)
		return (handle_one_philosopher(data, philo, left_fork), NULL);
	while (!simulation_stopped(data))
	{
		log_action(data, philo->philo_id, "is thinking");
		if (!chose_forks(data, philo, left_fork, right_fork))
			break ;
		if (!philo_eats(data, philo))
		{
			release_forks(data, left_fork, right_fork);
			break ;
		}
		release_forks(data, left_fork, right_fork);
		if (!philo_sleeps(data, philo))
			break ;
	}
	return (NULL);
}

void	create_threads(t_shared *data)
{
	int		i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		if (pthread_create(&data->philosophers[i].thread, NULL, &dining_routine,
							(void *)&data->philosophers[i]))
		{
			printf("Error creating threads!");
			cleanup_threads(data, i);
			return ;
		}
		i++;
	}
	i = 0;
	while (i < data->nb_of_philos)
	{
		if (pthread_join(data->philosophers[i].thread, NULL))
		{
			printf("Error joining threads!");
			return ;
		}
		i++;
	}
}
