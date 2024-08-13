/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_philosophers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:34:31 by ncollign          #+#    #+#             */
/*   Updated: 2024/08/13 11:33:22 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_fork(void)
/*
	This function creates a fork and returns the id of the fork
*/
{
	int	id;
	
	return (id);
}

void	routine(void)
/*
	This function simulate the routine of a philospher
*/
{
	
}

static void	create_philo(t_rules *rules, int i)
/*
	This function creates a philospher
*/
{
	t_philo philospher;

	philospher.id = i;
	philospher.dead = 0;
	philospher.nb_eat = 0;
	philospher.rules = rules;
	philospher.r_fork_id = create_fork();
}

void	init_philo(t_rules *rules)
/*
	This function initialize all philophers
*/
{
	int	i;

	i = 0;
	while (i <= rules->nb_philo)
	{
		create_philo(&rules, i);
		i++;
	}
}
