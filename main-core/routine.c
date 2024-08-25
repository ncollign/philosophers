/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:03:01 by ncollign          #+#    #+#             */
/*   Updated: 2024/08/25 18:40:07 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_think(t_philo *philo)
/*
	Function called when a philospher is thinking
	- Display a message
	- Wait 
*/
{
	printf("TIME %d is thinking\n", philo->id);
	usleep(1000);
}

static void	philo_sleep(t_philo *philo)
/*
	Function called when a philospher is sleeping
	- Display message
	- Wait
*/
{
	printf("TIME %d is sleeping\n", philo->id);
	usleep(philo->rules->time_to_sleep * 1000);
}

static void	philo_eat(t_philo *philo)
/*
	Function called when a philospher is eating
	- Lock forks right and left
	- Display a message
	- Wait while eating
*/
{
	long	new_meal;
	long	current_time;
	
	pthread_mutex_lock(&philo->rules->forks[philo->r_fork_id]);
	gettimeofday(&philo->rules->time, NULL);
	current_time = get_time_in_ms(philo->rules->time) - philo->rules->start_time;// A reproduire partout
	printf("%d %d has taken a fork\n",current_time, philo->id);
	pthread_mutex_lock(&philo->rules->forks[philo->l_fork_id]);
	printf("TIME %d has taken a fork\n", philo->id);
	printf("TIME %d is eating\n", philo->id);
	usleep(philo->rules->time_to_eat * 1000);
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->rules->forks[philo->r_fork_id]);
	pthread_mutex_unlock(&philo->rules->forks[philo->l_fork_id]);
	gettimeofday(&philo->rules->time, NULL);
	new_meal = get_time_in_ms(philo->rules->time);
	if (new_meal - philo->last_meal < philo->rules->time_to_die)
		philo->last_meal = new_meal; // Redéfinir le dernier repas
	else // Le philo est mort de faim
		philo->dead = 1;
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	gettimeofday(&philo->rules->time, NULL);
	philo->last_meal = get_time_in_ms(philo->rules->time); // Définir le premier repas (On considère que chaque philo commence l'estomac plein)
	while (1)
	{
		// Calculer temps depuis dernier repas
		// Comparer à time_to_die
		philo_eat(philo);
		if (philo->rules->nb_time_eat == philo->nb_eat)
			break;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}