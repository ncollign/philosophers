/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:03:01 by ncollign          #+#    #+#             */
/*   Updated: 2024/11/11 18:19:45 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_message(char *message, t_philo *philo)
{
	long	current_time;

	if (philo->rules->is_simulation_running)
	{
		current_time = get_current_time(philo->rules);
		pthread_mutex_lock(&philo->rules->print_mutex);
		printf("%ld %d %s\n", current_time, philo->id, message);
		pthread_mutex_unlock(&philo->rules->print_mutex);	
	}
}

static void	philo_think(t_philo *philo)
/*
	Function called when a philospher is thinking
	- Display a message
	- Wait 
*/
{
	print_message("is thinking", philo);
	usleep(1000);
}

static void	philo_sleep(t_philo *philo)
/*
	Function called when a philospher is sleeping
	- Display message
	- Wait
*/
{
	print_message("is sleeping", philo);
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
	long	current_time;
	
	pthread_mutex_lock(&philo->rules->forks[philo->l_fork_id]);
	print_message("has taken a fork", philo);
	if (philo->rules->nb_philo != 1)
	{
		pthread_mutex_lock(&philo->rules->forks[philo->r_fork_id]);
		print_message("has taken a fork", philo);
		print_message("is eating", philo);
		current_time = get_current_time(philo->rules);
		philo->last_meal = current_time;
		usleep(philo->rules->time_to_eat * 1000);
		philo->nb_eat++;
		pthread_mutex_unlock(&philo->rules->forks[philo->r_fork_id]);
		pthread_mutex_unlock(&philo->rules->forks[philo->l_fork_id]);
	}
	else
		usleep(philo->rules->time_to_die * 1000);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
    philo->last_meal = get_current_time(philo->rules);
	if (philo->id % 2)
		usleep(15000);
    while (philo->rules->is_simulation_running)
    {
        philo_eat(philo);
		philo_sleep(philo);
        philo_think(philo);
    }
    return (NULL);
}
