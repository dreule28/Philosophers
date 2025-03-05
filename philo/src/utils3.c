/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreule <dreule@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:13:48 by dreule            #+#    #+#             */
/*   Updated: 2025/03/05 17:17:08 by dreule           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	release_and_break(t_shared *data, int left_fork, int right_fork)
{
	release_forks(data, left_fork, right_fork);
	return ;
}