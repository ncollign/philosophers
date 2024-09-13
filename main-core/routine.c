/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:03:01 by ncollign          #+#    #+#             */
/*   Updated: 2024/08/28 12:28:14 by ncollign         ###   ########.fr       */
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
	long	current_time;

	current_time = get_current_time(philo->rules);
	printf("%ld %d is thinking\n", current_time, philo->id);
	usleep(1000);
}

static void	philo_sleep(t_philo *philo)
/*
	Function called when a philospher is sleeping
	- Display message
	- Wait
*/
{
	long	current_time;

	current_time = get_current_time(philo->rules);
	printf("%ld %d is sleeping\n", current_time, philo->id);
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
	current_time = get_current_time(philo->rules);
	printf("%ld %d has taken a fork\n",current_time, philo->id);
	pthread_mutex_lock(&philo->rules->forks[philo->l_fork_id]);
	current_time = get_current_time(philo->rules);
	printf("%ld %d has taken a fork\n", current_time, philo->id);
	current_time = get_current_time(philo->rules);
	printf("%ld %d is eating\n", current_time, philo->id);
	usleep(philo->rules->time_to_eat * 1000);
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->rules->forks[philo->r_fork_id]);
	pthread_mutex_unlock(&philo->rules->forks[philo->l_fork_id]);
	new_meal = get_current_time(philo->rules);
	if (new_meal - philo->last_meal < philo->rules->time_to_die)
		philo->last_meal = new_meal; // Redéfinir le dernier repas
	else // Le philo est mort de faim
		philo->dead = 1;
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	philo->last_meal = get_current_time(philo->rules); // Définir le premier repas (On considère que chaque philo commence l'estomac plein)
	while (1)
	{
		pthread_mutex_lock(&philo->rules->sim_mutex);
		if (philo->rules->simulation_running == 0)
		{
			pthread_mutex_unlock(&philo->rules->sim_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->rules->sim_mutex);

		philo_eat(philo);
		if (philo->nb_eat >= philo->rules->nb_time_eat && philo->rules->nb_time_eat != -1)
			break;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}