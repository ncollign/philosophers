/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:17:18 by ncollign          #+#    #+#             */
/*   Updated: 2024/10/26 20:58:29 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_simulation(t_rules rules)
{
	printf("Hello %d\n", rules.nb_philo);
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
            pthread_mutex_lock(&rules->sim_mutex);
            if (rules->simulation_running == 0)
            {
                pthread_mutex_unlock(&rules->sim_mutex);
                exit_simulation(*rules);
				return(NULL);
            }
            pthread_mutex_unlock(&rules->sim_mutex);

            time_since_last_meal = get_current_time(rules) - rules->philos[i].last_meal;
            if (time_since_last_meal > rules->time_to_die)
            {
                pthread_mutex_lock(&rules->sim_mutex);
                rules->simulation_running = 0;
                pthread_mutex_unlock(&rules->sim_mutex);
                printf("%ld %d died\n", get_current_time(rules), rules->philos[i].id);
				exit_simulation(*rules);
				return(NULL);
            }
            i++;
        }
        usleep(1000);
    }
	return(NULL);
}