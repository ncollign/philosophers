/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_philosophers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:34:31 by ncollign          #+#    #+#             */
/*   Updated: 2024/08/13 11:24:41 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(void)
{
	
}

static void	create_philo(void)
{
	
}

void	init_philo(t_rules *rules)
{
	int	i;

	i = 0;
	while (i <= rules->nb_philo)
	{
		create_philo();
		i++;
	}
}
