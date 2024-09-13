/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:17:18 by ncollign          #+#    #+#             */
/*   Updated: 2024/08/28 12:22:33 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*observer(void *arg)
{
	t_rules	*rules;
	long	current_time;
	int		i;

	rules = (t_rules *)arg;
	while (1)
	{
		i = 0;
		while (i < rules->nb_philo)
		{
			current_time = get_current_time(rules);
			pthread_mutex_lock(&rules->sim_mutex);
			if (current_time - rules->philos[i].last_meal > rules->time_to_die)
			{
				printf("%ld %d has died\n", current_time, rules->philos[i].id);
				rules->simulation_running = 0;
				pthread_mutex_unlock(&rules->sim_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&rules->sim_mutex);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}