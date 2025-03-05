/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreule <dreule@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:37:57 by dreule            #+#    #+#             */
/*   Updated: 2025/03/05 16:31:45 by dreule           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_not_nb(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] < '0' || argv[i] > '9')
			return (true);
		i++;
	}
	return (false);
}

int	init_args(char **argv, t_shared *data)
{
	data->nb_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->philos_done_eating = 0;
	data->sim_stop = false;
	if (argv[5])
		data->nb_of_meals = ft_atoi(argv[5]);
	else
		data->nb_of_meals = -1;
	data->sim_start = get_time_ms();
	return (1);
}

bool	check_args_and_init(char **argv, t_shared *data)
{
	if (ft_atoi(argv[1]) > 200 || ft_atoi(argv[1]) <= 0 || is_not_nb(argv[1]))
		return (error_init("Invalid number_of_philosophers!\n"), false);
	else if (ft_atoi(argv[2]) <= 0 || is_not_nb(argv[2]))
		return (error_init("Invalid time_to_die!\n"), false);
	if (ft_atoi(argv[3]) <= 0 || is_not_nb(argv[3]))
		return (error_init("Invalid time_to_eat!\n"), false);
	if (ft_atoi(argv[4]) <= 0 || is_not_nb(argv[4]))
		return (error_init("Invalid time_to_sleep!\n"), false);
	if (argv[5] && (ft_atoi(argv[5]) <= 0 || is_not_nb(argv[5])))
		return (error_init("Invalid number_of_meals!\n"), false);
	if (!init_args(argv, data))
	{
		free(data);
		return (false);
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_shared	data;

	if (argc < 5 || argc > 6)
		return (printf("Too many or too few Arguments!\n"), 1);
	if (!check_args_and_init(argv, &data))
		return (1);
}

// dorker valgrind --tool=hellgrind
// test values 5 800 200 200 7