/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_meals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreule <dreule@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:58:57 by dreule            #+#    #+#             */
/*   Updated: 2025/05/13 18:59:14 by dreule           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	release_forks(t_shared *data, int left_fork, int right_fork)
{
	pthread_mutex_unlock(&data->fork_mutexes[left_fork]);
	pthread_mutex_unlock(&data->fork_mutexes[right_fork]);
}

int	philo_eats(t_shared *data, t_philo *philo)
{
	bool	reached_quota;

	pthread_mutex_lock(&data->status_mutex);
	philo->time_last_meal = get_time_ms();
	pthread_mutex_unlock(&data->status_mutex);
	log_action(data, philo->philo_id, "is eating");
	custom_sleep(data, data->time_to_eat);
	pthread_mutex_lock(&data->status_mutex);
	philo->times_eaten++;
	reached_quota = (data->nb_of_meals > 0
			&& philo->times_eaten == data->nb_of_meals);
	pthread_mutex_unlock(&data->status_mutex);
	if (reached_quota)
	{
		pthread_mutex_lock(&data->stop_mutex);
		data->philos_done_eating++;
		pthread_mutex_unlock(&data->stop_mutex);
	}
	if (reached_quota)
		return (0);
	return (!simulation_stopped(data));
}
