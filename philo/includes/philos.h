/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psotto-m <psotto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 22:24:25 by psotto-m          #+#    #+#             */
/*   Updated: 2023/04/29 17:38:32 by psotto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H
# include <pthread.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				philo_id;
	int				meals_eaten;
	bool			hungry_philo;
	long long		last_meal;
	struct s_dinner	*dinner;
	pthread_t		thread;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
}	t_philo;

typedef struct s_dinner
{
	bool			errors;
	bool			print_key;
	int				nbr_philos;
	int				meals_till_full;
	int				satisfied_philos;
	long long		time_to_eat;
	long long		time_to_die;
	long long		start_time;
	long long		time_to_sleep;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meal_time;
	pthread_mutex_t	satisfied;
	pthread_mutex_t	print;
}	t_dinner;

// main.c

int				main(int ac, char **av);
bool			argument_handling(int ac, char **av, t_dinner *dinner);
void			cleanup(t_dinner *dinner);

// philo_life.c

void			*boring_life_of_philo(void *args);
void			philo_eats(t_philo *philo);
void			death_clock(t_dinner *dinner);
void			print_message(long long time, t_philo *philo, char msg);

// thread_creation.c

void			launch_philosophers(t_dinner *dinner);
pthread_mutex_t	*forks(int nbr_philos);
t_philo			*alloc_philos(t_dinner *dinner);
void			philos_actions(t_dinner *dinner);

// utils.c

int				ft_atoi(char *s, t_dinner *dinner);
void			is_digit(char *s, t_dinner *dinner);
void			error_handling(int error_flag, t_dinner *dinner);
long long		get_time(void);

#endif
