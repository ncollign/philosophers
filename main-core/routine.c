/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:03:01 by ncollign          #+#    #+#             */
/*   Updated: 2024/11/08 12:39:05 by ncollign         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->rules->print_mutex);
	printf("%ld %d is thinking\n", current_time, philo->id);
	pthread_mutex_unlock(&philo->rules->print_mutex);
	usleep(5000);
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
	pthread_mutex_lock(&philo->rules->print_mutex);
	printf("%ld %d is sleeping\n", current_time, philo->id);
	pthread_mutex_unlock(&philo->rules->print_mutex);
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
	
	// Prise des fourchettes
	// Les philp pairs prennent la gauche puis la droite
	// Les philo impairs prennent la droite puis la gauche
	// Pour éviter les deadlocks
	if (philo->id % 2 == 0)
    {
        // Philosophe pair : prend d'abord la fourchette de gauche, puis celle de droite
        pthread_mutex_lock(&philo->rules->forks[philo->l_fork_id]);
        current_time = get_current_time(philo->rules);
		pthread_mutex_lock(&philo->rules->print_mutex);
        printf("%ld %d has taken a fork\n", current_time, philo->id);
		pthread_mutex_unlock(&philo->rules->print_mutex);

        pthread_mutex_lock(&philo->rules->forks[philo->r_fork_id]);
        current_time = get_current_time(philo->rules);
		pthread_mutex_lock(&philo->rules->print_mutex);
        printf("%ld %d has taken a fork\n", current_time, philo->id);
		pthread_mutex_unlock(&philo->rules->print_mutex);
    }
    else
    {
        // Philosophe impair : prend d'abord la fourchette de droite, puis celle de gauche
        pthread_mutex_lock(&philo->rules->forks[philo->r_fork_id]);
        current_time = get_current_time(philo->rules);
		pthread_mutex_lock(&philo->rules->print_mutex);
        printf("%ld %d has taken a fork\n", current_time, philo->id);
		pthread_mutex_unlock(&philo->rules->print_mutex);

        pthread_mutex_lock(&philo->rules->forks[philo->l_fork_id]);
        current_time = get_current_time(philo->rules);
		pthread_mutex_lock(&philo->rules->print_mutex);
        printf("%ld %d has taken a fork\n", current_time, philo->id);
		pthread_mutex_unlock(&philo->rules->print_mutex);
    }
	current_time = get_current_time(philo->rules);
	pthread_mutex_lock(&philo->rules->print_mutex);
	printf("%ld %d is eating\n", current_time, philo->id);
	pthread_mutex_unlock(&philo->rules->print_mutex);
	philo->last_meal = current_time;
	usleep(philo->rules->time_to_eat * 1000);
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->rules->forks[philo->r_fork_id]);
	pthread_mutex_unlock(&philo->rules->forks[philo->l_fork_id]);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
    philo->last_meal = get_current_time(philo->rules);
    while (1)
    {
        philo_eat(philo);
		philo_sleep(philo);
        philo_think(philo);
    }
    return (NULL);
}
