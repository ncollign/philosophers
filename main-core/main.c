/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:19:05 by ncollign          #+#    #+#             */
/*   Updated: 2024/08/28 12:25:56 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
/*
	This function tests if a char is a digit
	Returns 1 if OK
	Returns 0 if NOK
*/
{
	if (c >= 48 && c <= 57)
	{
		return (1);
	}
	else
		return (0);
}

static int	is_valid_arg(char *arg)
/*
	Test if an argument is composed only of numbers
	Returns 1 if OK
	Returns 0 if NOK
*/
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (ft_isdigit(arg[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

static void	init_args(int argc, char **args, t_rules *rules)
/*
	This function verifies each argument and define it in a struct
	Exit the program if invalid argument
*/
{
	int	i;

	i = 1;
	(void)argc;
	while (args[i])
	{
		if (is_valid_arg(args[i]) == 0)
		{
			printf("Error\nInvalid arguments\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	rules->nb_philo = ft_atoi(args[1]);
	rules->time_to_die = ft_atoi(args[2]);
	rules->time_to_eat = ft_atoi(args[3]);
	rules->time_to_sleep = ft_atoi(args[4]);
	if (argc == 6)
		rules->nb_time_eat = ft_atoi(args[5]);
	else
		rules->nb_time_eat = -1;
	rules->simulation_running = 1;
    pthread_mutex_init(&rules->sim_mutex, NULL);
}

int	main(int argc, char **argv)
/*
	This function initialize the simulation
*/
{
	t_rules	rules;

	if (argc < 5 || argc > 6)
		printf("Error\nPlease enter only 4 or 5 arguments\n");
	else
	{
		init_args(argc, argv, &rules);
		init_philo(&rules);
	}
	return (1);
}
