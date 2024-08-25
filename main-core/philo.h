/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:19:08 by ncollign          #+#    #+#             */
/*   Updated: 2024/08/25 18:37:07 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>


typedef struct s_rules t_rules;
typedef struct s_philo
{
	pthread_t		thread_id;
	int				id;
	int				nb_eat;
	int				dead;
	long			last_meal;
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
	long				start_time;
	struct timeval		time;
}					t_rules;

void	init_philo(t_rules *rules);
int		ft_atoi(const char *str);
void	*routine(void *philo);
long	get_time_in_ms(struct timeval start)

#endif