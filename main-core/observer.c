/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:17:18 by ncollign          #+#    #+#             */
/*   Updated: 2024/11/11 21:33:48 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	cleanup(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_join(rules->philos[i].thread_id, NULL);
		i++;
	}
	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&rules->print_mutex);
	free(rules->philos);
	free(rules->forks);
}

static int	check_meal(t_rules *rules, int nb_eat_reached, int i)
{
	if ((nb_eat_reached == 1) && (rules->philos[i].nb_eat < rules->nb_time_eat))
		nb_eat_reached = 0;
	if (rules->nb_time_eat == -1)
		nb_eat_reached = 0;
	if (i == 4 && nb_eat_reached == 1)
	{
		pthread_mutex_lock(&rules->print_mutex);
		printf("Every philo has eat at least %d times\n",
			rules->nb_time_eat);
		pthread_mutex_unlock(&rules->print_mutex);
		rules->is_simulation_running = 0;
		return (1);
	}
	return (0);
}

static int	is_dead(t_rules *rules, int time_since_last_meal, int i)
{
	if (time_since_last_meal >= rules->time_to_die)
	{
		rules->is_simulation_running = 0;
		usleep(200);
		pthread_mutex_lock(&rules->print_mutex);
		printf("%ld %d died\n", get_current_time(rules),
			rules->philos[i].id);
		pthread_mutex_unlock(&rules->print_mutex);
		return (1);
	}
	return (0);
}

void	*observer(void *arg)
{
	t_rules	*rules;
	int		i;
	int		nb_eat_reached;
	long	time_since_last_meal;

	rules = (t_rules *)arg;
	usleep(1000);
	while (rules->is_simulation_running)
	{
		i = 0;
		nb_eat_reached = 1;
		while (i < rules->nb_philo)
		{
			time_since_last_meal = get_current_time(rules)
				- rules->philos[i].last_meal;
			if (is_dead(rules, time_since_last_meal, i))
				break ;
			if (check_meal(rules, nb_eat_reached, i))
				break ;
			i++;
		}
		usleep(1000);
	}
	cleanup(rules);
	return (NULL);
}
