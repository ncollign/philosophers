/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:17:18 by ncollign          #+#    #+#             */
/*   Updated: 2024/11/03 18:11:02 by ncollign         ###   ########.fr       */
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

	while (1)
	{
		i = 0;
		while (i < rules->nb_philo)
		{
			time_since_last_meal = get_current_time(rules) - rules->philos[i].last_meal;

			if (time_since_last_meal >= rules->time_to_die)
			{
				// Verrouiller le mutex d'affichage
				pthread_mutex_lock(&rules->print_mutex);
				printf("%ld %d died\n", get_current_time(rules), rules->philos[i].id);
				// Déverrouiller le mutex d'affichage
				pthread_mutex_unlock(&rules->print_mutex);

				// Nettoyer les ressources
				cleanup(rules);

				// Terminer le programme
				exit(0);
			}
			i++;
		}
		usleep(1000); // Pause pour éviter de surcharger le CPU
	}
	return (NULL);
}