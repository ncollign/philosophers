/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_arguments.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:19:05 by ncollign          #+#    #+#             */
/*   Updated: 2024/08/12 14:41:59 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
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

int	is_valid_arg(char *arg)
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

void	define_args(char **args)
/*
	This function verifies each argument and define it in a struct
	Exit the program if invalid argument
*/
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (is_valid_arg(args[i]) == 0)
		{
			printf("Error\nInvalid arguments\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	printf("Args OK\n");
}

int	main(int argc, char **argv)
/*
	This function initialize the simulation
*/
{
	if (argc < 5 || argc > 6)
		printf("Error\nPlease enter only 4 or 5 arguments\n");
	else
	{
		define_args(&argv[1]);
	}
	return (1);
}
