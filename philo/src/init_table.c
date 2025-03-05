/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreule <dreule@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:18:15 by dreule            #+#    #+#             */
/*   Updated: 2025/03/05 16:50:32 by dreule           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philos(t_shared *data)
{
	t_philo	*philos;
	int		i;

	philos = malloc(data->nb_of_philos * sizeof(t_philo));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < data->nb_of_philos)
	{
		philos[i].data = data;
		philos[i].philo_id = i + 1;
		philos[i].time_last_meal = get_time_ms();
		philos[i].times_eaten = 0;
		i++;
	}
	return (philos);
}

bool	init_fork_mutexes(pthread_mutex_t *fork)
{
	if (pthread_mutex_init(fork, NULL))
		return (false);
	return (true);
}

bool	init_forks(t_shared *data)
{
	int	i;

	data->fork_mutexes = malloc(data->nb_of_philos * sizeof(pthread_mutex_t));
	if (!data->fork_mutexes)
		return (false);
	i = 0;
	while (i < data->nb_of_philos)
	{
		if (!init_fork_mutexes(&data->fork_mutexes[i]))
		{
			while (i--)
				pthread_mutex_destroy(&data->fork_mutexes[i]);
			free(data->fork_mutexes);
			return (false);
		}
		i++;
	}
	return (true);
}

t_philo	*set_table(t_shared *data)
{
	t_philo	*philosophers;

	philosophers = init_philos(data);
	if (!philosophers)
		return (NULL);
	if (!init_forks(data))
	{
		free(philosophers);
		return (NULL);
	}

	data->philosophers = philosophers;
	return (philosophers);
}
