/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psotto-m <psotto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 20:24:34 by psotto-m          #+#    #+#             */
/*   Updated: 2023/04/29 17:38:47 by psotto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

void	philos_actions(t_dinner *dinner)
{
	int			i;

	i = 0;
	pthread_mutex_init (&dinner->print, NULL);
	dinner->start_time = get_time();
	while (i < dinner->nbr_philos)
	{
		pthread_create(&dinner->philos[i].thread, \
			NULL, &boring_life_of_philo, &dinner->philos[i]);
		i++;
	}
	usleep((dinner->time_to_die) * 1000);
	death_clock(dinner);
	i = 0;
	while (i < dinner->nbr_philos)
	{
		pthread_join(dinner->philos[i].thread, NULL);
		i++;
	}
	pthread_mutex_destroy (&dinner->print);
	if (dinner->print_key == true)
		printf("\n - 🥇 ALL PHILOS ARE SATISFIED 🥇 - \n");
}

t_philo	*alloc_philos(t_dinner *dinner)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * dinner->nbr_philos);
	while (i < dinner->nbr_philos)
	{
		philo[i].philo_id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].hungry_philo = true;
		philo[i].first_fork = &(dinner->forks[i]);
		philo[i].second_fork = &(dinner->forks[(i + 1) % dinner->nbr_philos]);
		if (i == 0)
		{
			philo[i].first_fork = &(dinner->forks \
			[(i + 1) % dinner->nbr_philos]);
			philo[i].second_fork = &(dinner->forks[i]);
		}
		philo[i].dinner = dinner;
		i++;
	}
	return (philo);
}

pthread_mutex_t	*forks(int nbr_philos)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * nbr_philos);
	while (i < nbr_philos)
		pthread_mutex_init(&forks[i++], NULL);
	return (forks);
}

void	launch_philosophers(t_dinner *dinner)
{
	pthread_mutex_init(&dinner->satisfied, NULL);
	pthread_mutex_init(&dinner->meal_time, NULL);
	dinner->forks = forks(dinner->nbr_philos);
	dinner->philos = alloc_philos(dinner);
	philos_actions(dinner);
}
