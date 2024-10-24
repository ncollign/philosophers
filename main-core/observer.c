/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:17:18 by ncollign          #+#    #+#             */
/*   Updated: 2024/10/21 14:23:28 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*observer(void *arg)
{
    t_rules	*rules = (t_rules *)arg;
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
                return (NULL);
            }
            pthread_mutex_unlock(&rules->sim_mutex);

            long time_since_last_meal = get_current_time(rules) - rules->philos[i].last_meal;
            if (time_since_last_meal > rules->time_to_die)
            {
                pthread_mutex_lock(&rules->sim_mutex);
                rules->simulation_running = 0;
                pthread_mutex_unlock(&rules->sim_mutex);

                printf("%ld %d died\n", get_current_time(rules), rules->philos[i].id);
                return (NULL);
            }
            i++;
        }
        usleep(1000); // Petite pause pour éviter de surcharger le CPU
    }
    return (NULL);
}