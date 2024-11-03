/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:03:01 by ncollign          #+#    #+#             */
/*   Updated: 2024/11/02 15:48:41 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_simulation_running(t_philo *philo)
/*
	This function checks if the simulation is still running
	If Running : Returns 1
	If Not Running : Returns 0
*/
{
	pthread_mutex_lock(&philo->rules->sim_mutex);
	if (philo->rules->simulation_running == 0)
	{
		pthread_mutex_unlock(&philo->rules->sim_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->rules->sim_mutex);
	return (1);
}

static int	philo_think(t_philo *philo)
/*
	Function called when a philospher is thinking
	- Display a message
	- Wait 
*/
{
	long	current_time;

	if (!is_simulation_running(philo))
		return (0);
	current_time = get_current_time(philo->rules);
	printf("%ld %d is thinking\n", current_time, philo->id);
	usleep(1000);
	return (1);
}

static int	philo_sleep(t_philo *philo)
/*
	Function called when a philospher is sleeping
	- Display message
	- Wait
*/
{
	long	current_time;

	if (!is_simulation_running(philo))
		return (0);
	current_time = get_current_time(philo->rules);
	printf("%ld %d is sleeping\n", current_time, philo->id);
	usleep(philo->rules->time_to_sleep * 1000);
	return (1);
}

static int	philo_eat(t_philo *philo)
/*
	Function called when a philospher is eating
	- Lock forks right and left
	- Display a message
	- Wait while eating
*/
{
	long	current_time;
	
	if (!is_simulation_running(philo))
		return (0);
	// Prise des fourchettes
	// Les philp pairs prennent la gauche puis la droite
	// Les philo impairs prennent la droite puis la gauche
	// Pour éviter les deadlocks
	if (philo->id % 2 == 0)
    {
        // Philosophe pair : prend d'abord la fourchette de gauche, puis celle de droite
        pthread_mutex_lock(&philo->rules->forks[philo->l_fork_id]);
        current_time = get_current_time(philo->rules);
        printf("%ld %d has taken a fork\n", current_time, philo->id);

        pthread_mutex_lock(&philo->rules->forks[philo->r_fork_id]);
        current_time = get_current_time(philo->rules);
        printf("%ld %d has taken a fork\n", current_time, philo->id);
    }
    else
    {
        // Philosophe impair : prend d'abord la fourchette de droite, puis celle de gauche
        pthread_mutex_lock(&philo->rules->forks[philo->r_fork_id]);
        current_time = get_current_time(philo->rules);
        printf("%ld %d has taken a fork\n", current_time, philo->id);

        pthread_mutex_lock(&philo->rules->forks[philo->l_fork_id]);
        current_time = get_current_time(philo->rules);
        printf("%ld %d has taken a fork\n", current_time, philo->id);
    }


	
	current_time = get_current_time(philo->rules);
	printf("%ld %d is eating\n", current_time, philo->id);
	usleep(philo->rules->time_to_eat * 1000);
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->rules->forks[philo->r_fork_id]);
	pthread_mutex_unlock(&philo->rules->forks[philo->l_fork_id]);
	get_current_time(philo->rules);
	philo->last_meal = current_time;
	return (1);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
    philo->last_meal = get_current_time(philo->rules);
    while (is_simulation_running(philo))
    {
        if (!is_simulation_running(philo))
			break;
        if (!philo_eat(philo))
            break;
		if (!philo_sleep(philo))
			break;
        if (!philo_think(philo))
			break;
    }
	printf("Philo OK\n");
    return (NULL);
}
