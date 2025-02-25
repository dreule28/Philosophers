/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreule <dreule@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:46:11 by dreule            #+#    #+#             */
/*   Updated: 2025/02/25 13:50:01 by dreule           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_action(t_shared *data, int philo_id, char *log_message)
{
	pthread_mutex_lock(&data->log_mutex);
	if (!data->sim_stop)
		printf("%ld %d %s\n", data->sim_start, philo_id, log_message);
	pthread_mutex_unlock(&data->log_mutex);
}
