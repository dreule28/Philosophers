/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreule <dreule@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:20:19 by dreule            #+#    #+#             */
/*   Updated: 2025/03/07 17:36:12 by dreule           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_and_join_monitor(t_shared *data)
{
	if (pthread_create(&data->monitor, NULL, &monitor_routine, data))
	{
		printf("Error creating monitor!");
		cleanup_threads(data, data->nb_of_philos);
		return ;
	}
	if (pthread_join(data->monitor, NULL))
	{
		printf("Error joining monitor!");
		return ;
	}
}

void	*monitor_routine(void *arg)
{
	t_shared	*data;
	int			i;
	long		curr_time;
	data = (t_shared *)arg;
	while (!simulation_stopped(data))
	{
		i = 0;
		while (i < data->nb_of_philos)
		{
			pthread_mutex_lock(&data->status_mutex);
			curr_time = get_time_ms();
			if (curr_time - data->philosophers[i].time_last_meal > data->time_to_die)
			{
				pthread_mutex_lock(&data->stop_mutex);
				if (!data->sim_stop)
				{
					data->sim_stop = 1;
					pthread_mutex_unlock(&data->stop_mutex);
					log_action(data, data->philosophers[i].philo_id, "died");
				}
				else
					pthread_mutex_unlock(&data->stop_mutex);
				pthread_mutex_unlock(&data->status_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->status_mutex);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
