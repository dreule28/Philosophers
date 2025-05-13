/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+:        +:    */
/*   By: dreule <dreule@student.42.fr>              +# +:      +#       */
/*                                                +#+#+#+#+#  +#          */
/*   Created: 2025/02/20 12:09:23 by dreule            #+#    #+#             */
/*   Updated: 2025/05/12 10:09:03 by dreule           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	delay_start(t_philo *philo)
{
	if (philo->philo_id % 2 != 0)
		usleep(1000);
}

bool	try_to_take_fork(t_shared *data, t_philo *philo, int fork_id)
{
	if (!pthread_mutex_lock(&data->fork_mutexes[fork_id]))
	{
		log_action(data, philo->philo_id, "has taken a fork");
		return (true);
	}
	return (false);
}

bool	take_second_fork(t_shared *data, t_philo *philo, int f_fork, int s_fork)
{
	while (!simulation_stopped(data))
	{
		if (try_to_take_fork(data, philo, s_fork))
			return (true);
		usleep(100);
	}
	pthread_mutex_unlock(&data->fork_mutexes[f_fork]);
	return (false);
}

int	chose_forks(t_shared *data, t_philo *philo, int left_fork, int right_fork)
{
	int	first;
	int	second;

	delay_start(philo);
	if (philo->philo_id % 2 == 0)
	{
		first = right_fork;
		second = left_fork;
	}
	else
	{
		first = left_fork;
		second = right_fork;
	}
	while (!simulation_stopped(data))
	{
		if (try_to_take_fork(data, philo, first))
		{
			if (take_second_fork(data, philo, first, second))
				return (1);
			return (0);
		}
		usleep(100);
	}
	return (0);
}


