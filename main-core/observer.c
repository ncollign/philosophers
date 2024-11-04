/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:17:18 by ncollign          #+#    #+#             */
/*   Updated: 2024/11/04 17:17:21 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_rules *rules)
{
	int i;

	// Détruire les mutex des fourchettes
	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	// Détruire le mutex d'affichage
	pthread_mutex_destroy(&rules->print_mutex);

	// Libérer la mémoire allouée
	free(rules->philos);
	free(rules->forks);
}

void	*observer(void *arg)
{
	t_rules	*rules = (t_rules *)arg;
	long	time_since_last_meal;
	int		i;
	int		nb_eat_reached;
	
	while (1)
	{
		i = 0;
		nb_eat_reached = 1;
		while (i < rules->nb_philo)
		{
			time_since_last_meal = get_current_time(rules) - rules->philos[i].last_meal;
			if (time_since_last_meal >= rules->time_to_die)
			{
				pthread_mutex_lock(&rules->print_mutex);
				printf("%ld %d died\n", get_current_time(rules), rules->philos[i].id);
				pthread_mutex_unlock(&rules->print_mutex);
				cleanup(rules);
				exit(EXIT_SUCCESS);
			}
			if ((nb_eat_reached == 1) && (rules->philos[i].nb_eat < rules->nb_time_eat))
				nb_eat_reached = 0;
			if (i == 4 && nb_eat_reached == 1)
			{
				printf("Every philo has eat at leat %d times\n", rules->nb_time_eat);
				cleanup(rules);
				exit(EXIT_SUCCESS);
			}
				
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}