/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:48:47 by ncollign          #+#    #+#             */
/*   Updated: 2024/08/19 10:57:47 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(void)
/*
	This function simulate the routine of a philospher
*/
{
	
}

void	start_simulation(t_rules *rules)
{
	int i;

	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_create(&(rules->philos[i].thread_id), NULL, routine, &(rules->philos[i]));
		i++;
	}
	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_join(rules->philos[i].thread_id, NULL);
		i++;
	}
}
