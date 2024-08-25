/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:19:08 by ncollign          #+#    #+#             */
/*   Updated: 2024/08/25 17:47:00 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_rules t_rules;
typedef struct s_philo
{
	pthread_t		thread_id;
	int				id;
	int				nb_eat;
	int				dead;
	int				r_fork_id;
	int				l_fork_id;
	t_rules			*rules;
}					t_philo;

typedef struct s_rules
{
	t_philo				*philos;
	pthread_mutex_t		*forks;
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_time_eat;
}					t_rules;

void	init_philo(t_rules *rules);
int		ft_atoi(const char *str);
void	routine(t_philo *philo);

#endif