/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreule <dreule@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:18:15 by dreule            #+#    #+#             */
/*   Updated: 2025/02/20 11:52:16 by dreule           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*add_chair(t_shared *data, int i)
{
	t_philo	*new_chair;

	new_chair = malloc(sizeof(t_philo));
	if (!new_chair)
		return (NULL);
	new_chair->philo_id = i;
	if (pthread_mutex_init(&new_chair->l_fork_mutex, NULL))
		return (NULL);
	new_chair->times_eaten = 0;
	new_chair->time_last_meal = data->sim_start;
	new_chair->right = NULL;
	new_chair->left = NULL;
	return (new_chair);
}

void	place_chair_at_table(t_philo *new_chair, t_philo **table, t_philo **last)
{
	if (!*table)
	{
		*table = new_chair;
		*last = new_chair;
	}
	else
	{
		new_chair->left = *last;
		(*last)->right = new_chair;
		*last = new_chair;
	}
}

void	get_right_fork(t_philo *table, int nb_of_philos)
{
	t_philo	*curr;

	curr = table;
	while (curr != table)
	{
		if (nb_of_philos == 1)
		{
			curr->r_fork_mutex = NULL;
			return ;
		}
		curr->r_fork_mutex = &curr->right->l_fork_mutex;
		curr = curr->right;
	}
}

t_philo	*set_table(t_shared *data)
{
	t_philo	*table;
	t_philo	*last;
	t_philo	*new_chair;
	int		i;

	i = 1;
	while (i <= data->nb_of_philos)
	{
		new_chair = add_chair(data, i);
		i++;
		last = place_chair_at_table(new_chair, table, last);
		if (!table)
			table = last;
	}
	last->right = table;
	table->left = last;
	get_right_fork(table, data->nb_of_philos);
	return (table);
}
