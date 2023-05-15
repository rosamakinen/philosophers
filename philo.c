/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:16:46 by rmakinen          #+#    #+#             */
/*   Updated: 2023/05/15 14:14:24 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_num(char *arg, int check)
{
	int	i;

	i = 0;
	if (check != 0)
		return (check);
	while (arg[i] != '\0')
	{
	//	printf("numbers to go through %c\n", arg[i]);
		if (arg[i] > 47 && arg[i] < 58)
			i++;
		else
			return (1);
	}
	return (0);
}

int	is_negative(char *arg, int check)
{
	if (check != 0)
		return (check);
	printf("neg: %s\n", arg);
	if (arg[0] == '-' || arg[0] == '+')
		return (1);
	return (0);
}

int	check_input(char *arg)
{
	int	check;
	check = 0;
	check = is_negative(arg, check);
	printf("1: %i\n", check); //PRINTING
	check = is_num(arg, check);
	printf("2: %i\n", check); //PRINTING
	return (check);
}

int	main(int argc, char **argv)
{
	int	check;
	int	i;

	check = 0;
	i = 1;
	if (argc < 5 || argc > 6)
		exit (1);
	while (i < argc)
	{
		printf("arg %i\n", i);
		check = check_input(argv[i]);
		if (check != 0)
			exit (1);
		i++;
	}
//	make_threads();
	return (0);
}
