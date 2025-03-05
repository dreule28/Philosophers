/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreule <dreule@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:56:39 by dreule            #+#    #+#             */
/*   Updated: 2025/03/05 16:34:21 by dreule           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clear_up_table(t_shared *data)
{
	int		i;

	if (!data->philosophers)
		return ;
	i = 0;
	if (data->fork_mutexes)
	{
		while (i < data->nb_of_philos)
		{
			if (pthread_mutex_destroy(&data->fork_mutexes[i]))
				printf("Failed to destroy mutex\n");
			i++;
		}
		free(data->fork_mutexes);
	}
	free(data->philosophers);
	pthread_mutex_destroy(&data->log_mutex);
	pthread_mutex_destroy(&data->status_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
}

void	cleanup_threads(t_shared *data, int count)
{
	int	i;

	i = 0;
	while (i++ < count)
	{
		pthread_join(&data->philosophers->thread[i], NULL);
		free(&data->philosophers[i]);
		free(data);
	}
}