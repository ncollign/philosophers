/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:03:01 by ncollign          #+#    #+#             */
/*   Updated: 2024/08/25 17:56:02 by ncollign         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->rules->forks[philo->r_fork_id]);
	printf("TIME %d has taken a fork\n", philo->id);
	pthread_mutex_lock(&philo->rules->forks[philo->l_fork_id]);
	printf("TIME %d has taken a fork\n", philo->id);
	printf("TIME %d is eating\n", philo->id);
	usleep(philo->rules->time_to_eat * 1000);
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->rules->forks[philo->r_fork_id]);
	pthread_mutex_unlock(&philo->rules->forks[philo->l_fork_id]);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
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