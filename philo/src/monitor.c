/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreule <dreule@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:20:19 by dreule            #+#    #+#             */
/*   Updated: 2025/05/14 12:14:28 by dreule           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	has_eaten_enough(t_shared *data, int philo_index)
{
	return (data->nb_of_meals > 0
		&& data->philosophers[philo_index].times_eaten >= data->nb_of_meals);
}

bool	check_philosopher_death(t_shared *data, int i)
{
	long	now;
	long	death_time;
	long	time_since_last_meal;
	int		philo_id;

	now = get_time_ms();
	time_since_last_meal = now - data->philosophers[i].time_last_meal;
	if (time_since_last_meal > data->time_to_die)
	{
		death_time = data->philosophers[i].time_last_meal + data->time_to_die;
		philo_id = data->philosophers[i].philo_id;
		pthread_mutex_lock(&data->log_mutex);
		printf("%ld %d %s\n", death_time - data->sim_start, philo_id, "died");
		pthread_mutex_unlock(&data->log_mutex);
		set_simulation_stop(data);
		return (true);
	}
	return (false);
}

bool	all_philosophers_done_eating(t_shared *data, int done_count)
{
	if (data->nb_of_meals > 0 && done_count == data->nb_of_philos)
	{
		set_simulation_stop(data);
		return (true);
	}
	return (false);
}

void	set_simulation_stop(t_shared *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->sim_stop = true;
	pthread_mutex_unlock(&data->stop_mutex);
}

void	*monitor_routine(void *arg)
{
	t_shared	*data;
	int			i;
	int			done;

	data = (t_shared *)arg;
	while (!simulation_stopped(data))
	{
		done = 0;
		i = 0;
		while (i < data->nb_of_philos)
		{
			pthread_mutex_lock(&data->status_mutex);
			if (has_eaten_enough(data, i))
				done++;
			else if (check_philosopher_death(data, i))
				return (pthread_mutex_unlock(&data->status_mutex), NULL);
			pthread_mutex_unlock(&data->status_mutex);
			i++;
		}
		if (all_philosophers_done_eating(data, done))
			return (NULL);
		usleep(200);
	}
	return (NULL);
}
