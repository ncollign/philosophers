/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:34:31 by ncollign          #+#    #+#             */
/*   Updated: 2024/10/26 21:34:57 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	create_philo(t_rules *rules, int i)
/*
	This function creates a philospher
*/
{
	t_philo	philospher;

	philospher.id = i;
	philospher.dead = 0;
	philospher.nb_eat = 0;
	philospher.r_fork_id = i;
	philospher.rules = rules;
	if (i == rules->nb_philo)
		philospher.l_fork_id = 1;
	else
		philospher.l_fork_id = i + 1;
	rules->philos[i - 1] = philospher;
}

void	init_philo(t_rules *rules)
/*
	This function initialize all philophers
*/
{
	int	i;

	rules->philos = malloc(sizeof(t_philo) * rules->nb_philo);
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
	i = 1;
	while (i <= rules->nb_philo)
	{
		pthread_mutex_init(&rules->forks[i - 1], NULL);
		create_philo(rules, i);
		i++;
	}
}
