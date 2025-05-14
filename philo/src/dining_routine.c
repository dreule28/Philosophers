/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreule <dreule@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:22:38 by dreule            #+#    #+#             */
/*   Updated: 2025/05/14 10:18:08 by dreule           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_initial_timing(t_shared *data, t_philo *philo)
{
	if (philo->philo_id % 2 != 0)
		custom_sleep(data, data->time_to_eat);
	if (philo->philo_id % 2 == 0)
		usleep(200);
	else
		usleep(0);
}

bool	philo_cycle(t_shared *data, t_philo *philo, int l_fork, int r_fork)
{
	log_action(data, philo->philo_id, "is thinking");
	if (!chose_forks(data, philo, l_fork, r_fork))
		return (false);
	if (!philo_eats(data, philo))
	{
		release_forks(data, l_fork, r_fork);
		return (false);
	}
	release_forks(data, l_fork, r_fork);
	if (!philo_sleeps(data, philo))
		return (false);
	if (data->time_to_sleep < data->time_to_eat)
		custom_sleep(data, data->time_to_eat - data->time_to_sleep);
	return (true);
}

void	*dining_routine(void *arg)
{
	t_philo		*philo;
	t_shared	*data;
	int			left_fork;
	int			right_fork;

	philo = (t_philo *)arg;
	data = philo->data;
	left_fork = philo->philo_id - 1;
	right_fork = philo->philo_id % data->nb_of_philos;
	if (data->nb_of_philos == 1)
		handle_one_philosopher(data, philo, left_fork);
	handle_initial_timing(data, philo);
	while (!simulation_stopped(data))
	{
		if (!philo_cycle(data, philo, left_fork, right_fork))
			break ;
	}
	return (NULL);
}
