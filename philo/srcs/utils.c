/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psotto-m <psotto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:11:07 by psotto-m          #+#    #+#             */
/*   Updated: 2023/04/28 17:05:40 by psotto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

long long	get_time(void)
{
	struct timeval	tv;
	long long		time_ms;

	gettimeofday(&tv, NULL);
	time_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_ms);
}

void	error_handling(int error_flag, t_dinner *dinner)
{
	if (error_flag == 1 && dinner->errors == false)
		printf("Wrong number of arguments 💩\n");
	if (error_flag == 2 && dinner->errors == false)
		printf("Only use numbers please 💩\n");
	if (error_flag == 3 && dinner->errors == false)
		printf("No negative numbers please 💩\n");
	dinner->errors = true;
}

void	is_digit(char *s, t_dinner *dinner)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if ((s[i] < '0' || s[i] > '9') && (s[i] != '+' && s[i] != '-'))
			error_handling(2, dinner);
		i++;
	}
}

int	ft_atoi(char *s, t_dinner *dinner)
{
	long	num;

	num = 0;
	is_digit(s, dinner);
	while (*s == 32 || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			error_handling(3, dinner);
		s++;
	}	
	while (*s && *s >= '0' && *s <= '9')
	{
		num = num * 10 + (*s - '0');
		s++;
	}
	return ((int)num);
}
