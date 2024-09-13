/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:20:59 by ncollign          #+#    #+#             */
/*   Updated: 2024/08/28 12:34:28 by ncollign         ###   ########.fr       */
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

long get_current_time(t_rules *rules)
{
    struct timeval current_time;
    long milliseconds;

    gettimeofday(&current_time, NULL);
    milliseconds = (current_time.tv_sec - rules->start_time.tv_sec) * 1000;
    milliseconds += (current_time.tv_usec - rules->start_time.tv_usec) / 1000;
    return milliseconds;
}