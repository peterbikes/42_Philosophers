/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psotto-m <psotto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 22:14:35 by psotto-m          #+#    #+#             */
/*   Updated: 2023/04/28 19:01:06 by psotto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

void	cleanup(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->nbr_philos)
		pthread_mutex_destroy(&dinner->forks[i++]);
	free(dinner->forks);
	free(dinner->philos);
}

bool	argument_handling(int ac, char **av, t_dinner *dinner)
{
	dinner->print_key = true;
	dinner->satisfied_philos = 0;
	dinner->nbr_philos = ft_atoi(av[1], dinner);
	dinner->time_to_die = ft_atoi(av[2], dinner);
	dinner->time_to_eat = ft_atoi(av[3], dinner);
	dinner->time_to_sleep = ft_atoi(av[4], dinner);
	dinner->meals_till_full = -1;
	if (ac == 6)
		dinner->meals_till_full = ft_atoi(av[5], dinner);
	return (dinner->errors);
}

int	main(int ac, char **av)
{
	t_dinner	dinner;

	dinner.errors = false;
	if (ac != 5 && ac != 6)
	{
		error_handling(1, &dinner);
		return (0);
	}
	if (!argument_handling(ac, av, &dinner))
	{
		launch_philosophers(&dinner);
		cleanup(&dinner);
	}
	return (0);
}
