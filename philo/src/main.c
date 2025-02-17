/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreule <dreule@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:37:57 by dreule            #+#    #+#             */
/*   Updated: 2025/02/17 16:17:20 by dreule           ###   ########.fr       */
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

int	check_args(char **argv)
{
	if (ft_atoi(argv[1]) > PHILO_MAX || ft_atoi(argv[1]) <= 0 || is_not_nb(argv[1]))
		return (error_init("Invalid number_of_philosophers!\n"), 0);
	else if (ft_atoi(argv[2]) <= 0 || is_not_nb(argv[2]))
		return (error_init("Invalid time_to_die!\n"), 0);
	if (ft_atoi(argv[3]) <= 0 || is_not_nb(argv[3]))
		return (error_init("Invalid time_to_eat!\n"), 0);
	if (ft_atoi(argv[4]) <= 0 || is_not_nb(argv[4]))
		return (error_init("Invalid time_to_sleep!\n"), 0);
	if (argv[5] && (ft_atoi(argv[5]) <= 0 || is_not_nb(argv[5])))
		return (error_init("Invalid number_of__times_each_philosopher_must_eat!\n"), 0);
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (printf("Too many or too few Arguments!\n"), 1);
	if (!check_args(argv))
		return (1);
}

// dorker valgrind --tool=hellgrind
