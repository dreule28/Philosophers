/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreule <dreule@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:20:19 by dreule            #+#    #+#             */
/*   Updated: 2025/02/19 11:06:06 by dreule           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	min_count;
	int	i;
	int	nb;

	i = 0;
	min_count = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			min_count++;
		i++;
	}
	nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (min_count % 2 != 0)
		nb = -nb;
	return (nb);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	error_init(char *str)
{
	write(2, str, ft_strlen(str));
}

time_t	get_time_ms()
{
	time_t			time_in_ms;
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	time_in_ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (time_in_ms);
}
