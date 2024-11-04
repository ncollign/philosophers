/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:48:47 by ncollign          #+#    #+#             */
/*   Updated: 2024/11/04 17:28:31 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_simulation(t_rules *rules)
{
	int			i;
	pthread_t	observer_thread;

	//rules->simulation_running = 1;
    //pthread_mutex_init(&rules->sim_mutex, NULL);
	pthread_mutex_init(&rules->print_mutex, NULL);
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
}
