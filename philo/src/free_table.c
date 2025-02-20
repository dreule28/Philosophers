/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreule <dreule@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:56:39 by dreule            #+#    #+#             */
/*   Updated: 2025/02/20 17:11:19 by dreule           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clear_up_table(t_shared *data)
{
	t_philo	*curr;
	t_philo	*next;
	int		i;

	if (!data->philosophers)
		return ;
	curr = data->philosophers;
	i = 0;
	while (i++ < data->nb_of_philos)
	{
		next = curr->right;
		pthread_mutex_destroy(&curr->l_fork_mutex);
		free(&curr->l_fork_mutex);
		free(curr);
		curr = next;
	}
	pthread_mutex_destroy(&data->log_mutex);
}
