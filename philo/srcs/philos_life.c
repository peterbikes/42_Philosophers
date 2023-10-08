/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_life.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psotto-m <psotto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:37:55 by psotto-m          #+#    #+#             */
/*   Updated: 2023/10/08 17:06:58 by psotto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

void	print_message(long long time, t_philo *philo, char msg)
{
	pthread_mutex_lock (&philo->dinner->print);
	if (msg == 'F' && philo->dinner->print_key == true)
		printf("⌚ %lld %d has taken a fork 🪥\n", time, philo->philo_id);
	if (msg == 'E' && philo->dinner->print_key == true)
		printf("⌚ %lld %d is eating 🍔🍟\n", time, philo->philo_id);
	if (msg == 'S' && philo->dinner->print_key == true)
	{
		pthread_mutex_unlock (&philo->dinner->print);
		printf("⌚ %lld %d is sleeping 💤\n", time, philo->philo_id);
		usleep(philo->dinner->time_to_sleep * 1000);
		pthread_mutex_lock (&philo->dinner->print);
		if (philo->dinner->print_key == true)
		{
			pthread_mutex_unlock (&philo->dinner->print);
			printf("⌚ %lld %d is thinking 🤔\n", time, philo->philo_id);
			return ;
		}
		pthread_mutex_unlock (&philo->dinner->print);
		return ;
	}
	pthread_mutex_unlock (&philo->dinner->print);
}

bool	death_helper(t_dinner	*dinner)
{
	pthread_mutex_lock(&dinner->meal_time);
	if (dinner->print_key == false || \
	dinner->satisfied_philos == dinner->nbr_philos)
	{
		pthread_mutex_unlock(&dinner->meal_time);
		return (true);
	}
	pthread_mutex_unlock(&dinner->meal_time);
	return (false);
}

void	death_clock(t_dinner	*dinner)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i != dinner->nbr_philos)
		{
			pthread_mutex_lock(&dinner->meal_time);
			if ((get_time() - dinner->philos[i].last_meal) \
			>= dinner->time_to_die && dinner->philos[i].hungry_philo == true)
			{
				pthread_mutex_unlock(&dinner->meal_time);
				pthread_mutex_lock(&dinner->print);
				dinner->print_key = false;
				pthread_mutex_unlock(&dinner->print);
				printf("⌚ %lld %d is dead 💀💀💀\n", \
				(get_time() - dinner->start_time), dinner->philos[i].philo_id);
				break ;
			}
			pthread_mutex_unlock(&dinner->meal_time);
			i++;
		}
		if (death_helper(dinner))
			break ;
	}
}

void	philo_eats(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	print_message((get_time() - philo->dinner->start_time), philo, 'F');
	if (philo->dinner->nbr_philos == 1)
	{
		usleep(philo->dinner->time_to_die * 1001);
		pthread_mutex_unlock(philo->first_fork);
		return ;
	}
	pthread_mutex_lock(philo->second_fork);
	print_message((get_time() - philo->dinner->start_time), philo, 'E');
	philo->meals_eaten++;
	pthread_mutex_lock(&philo->dinner->meal_time);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->dinner->meal_time);
	usleep(philo->dinner->time_to_eat * 1000);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

void	*boring_life_of_philo(void *args)
{
	t_philo	*philo;

	philo = args;
	pthread_mutex_lock(&philo->dinner->meal_time);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->dinner->meal_time);
	while (philo->meals_eaten != philo->dinner->meals_till_full)
	{
		pthread_mutex_lock (&philo->dinner->print);
		if (philo->dinner->print_key == false)
		{
			pthread_mutex_unlock (&philo->dinner->print);
			break ;
		}
		pthread_mutex_unlock (&philo->dinner->print);
		philo_eats(philo);
		if (philo->meals_eaten != philo->dinner->meals_till_full \
		&& philo->dinner->nbr_philos != 1)
			print_message((get_time() - philo->dinner->start_time), philo, 'S');
	}
	philo->hungry_philo = false;
	pthread_mutex_lock (&philo->dinner->meal_time);
	philo->dinner->satisfied_philos++;
	pthread_mutex_unlock (&philo->dinner->meal_time);
	return (NULL);
}
