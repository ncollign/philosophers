/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:20:59 by ncollign          #+#    #+#             */
/*   Updated: 2024/08/25 18:26:08 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
/*
	This function converts str into int
*/
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

long get_time_in_ms(struct timeval start)
{
	struct timeval current;
	long seconds;
	long useconds;
	long milliseconds;

	// Obtenez le temps actuel
	gettimeofday(&current, NULL);

	// Calculez la différence entre le temps actuel et le temps de départ
	seconds = current.tv_sec - start.tv_sec;
	useconds = current.tv_usec - start.tv_usec;

	// Convertir en millisecondes
	milliseconds = (seconds * 1000) + (useconds / 1000);

	return (milliseconds);
}