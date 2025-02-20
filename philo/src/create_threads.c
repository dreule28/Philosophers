/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreule <dreule@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:09:23 by dreule            #+#    #+#             */
/*   Updated: 2025/02/20 15:04:55 by dreule           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	(void)arg;
	return (NULL) ;
}

void	create_threads(t_shared *data)
{
	int		i;
	t_philo	*chair;

	i = 0;
	chair = data->philosophers;
	while (i++ < data->nb_of_philos)
	{
		if (pthread_create(&chair->thread_id, NULL, &routine, (void *) data))
		{
			printf("Error creating threads!");
			return ;
		}
		chair = chair->right;
	}
	i = 0;
	chair = data->philosophers;
	while (i++ < data->nb_of_philos)
	{
		if (pthread_join(chair->thread_id, NULL))
		{
			printf("Error joining threads!");
			return ;
		}
		chair = chair->right;
	}
}
