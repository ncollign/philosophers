/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:34:31 by ncollign          #+#    #+#             */
/*   Updated: 2024/11/08 13:38:15 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	create_philo(t_rules *rules, int i)
/*
	This function creates a philosopher
*/
{
	t_philo	philosopher;

	philosopher.id = i + 1;
	philosopher.nb_eat = 0;
	philosopher.last_meal = get_current_time(rules);
	philosopher.l_fork_id = i;
	philosopher.rules = rules;
	if (i == 0)
		philosopher.r_fork_id = rules->nb_philo - 1;
	else
		philosopher.r_fork_id = i - 1;
	rules->philos[i] = philosopher;
}

void	init_philo(t_rules *rules)
/*
	This function initialize all philophers
*/
{
	int	i;

	rules->philos = malloc(sizeof(t_philo) * rules->nb_philo);
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_init(&rules->forks[i], NULL);
		create_philo(rules, i);
		i++;
	}
}
