/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreule <dreule@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:56:39 by dreule            #+#    #+#             */
/*   Updated: 2025/02/24 16:56:18 by dreule           ###   ########.fr       */
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
		while (i++ < data->nb_of_philos)
		{
			pthread_mutex_destroy(&data->fork_mutexes[i]);
		}
		free(data->fork_mutexes);
	}
	free(data->philosophers);
	pthread_mutex_destroy(&data->log_mutex);
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