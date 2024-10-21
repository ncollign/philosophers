/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:48:47 by ncollign          #+#    #+#             */
/*   Updated: 2024/10/21 14:09:18 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_simulation(t_rules *rules)
{
	int			i;
	pthread_t	observer_thread;

	gettimeofday(&rules->start_time, NULL);
	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_create(&(rules->philos[i].thread_id), NULL, routine, &(rules->philos[i]));
		i++;
	}
	pthread_create(&observer_thread, NULL, observer, rules);
	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_join(rules->philos[i].thread_id, NULL);
		i++;
	}
	pthread_join(observer_thread, NULL);
	pthread_mutex_destroy(&rules->sim_mutex);
	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	free(rules->philos);
	free(rules->forks);
}
