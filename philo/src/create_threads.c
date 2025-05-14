/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreule <dreule@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:18:07 by dreule            #+#    #+#             */
/*   Updated: 2025/05/14 14:36:13 by dreule           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	failed_dining(t_shared *data, int *i)
{
	int	pos;

	pos = *i;
	pthread_mutex_lock(&data->stop_mutex);
	data->sim_stop = 1;
	pthread_mutex_unlock(&data->stop_mutex);
	printf("Error creating threads!");
	save_threads(data, pos);
	return ;
}

void	create_and_join_monitor(t_shared *data)
{
	if (pthread_create(&data->monitor, NULL, &monitor_routine, data))
	{
		printf("Error creating monitor!");
		save_threads(data, data->nb_of_philos);
		return ;
	}
	pthread_join(data->monitor, NULL);
}

void	create_threads(t_shared *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		if (pthread_create(&data->philosophers[i].thread, NULL, &dining_routine,
				(void *)&data->philosophers[i]))
			failed_dining(data, &i);
		i++;
	}
	create_and_join_monitor(data);
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
