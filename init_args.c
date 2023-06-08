/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:30:10 by rmakinen          #+#    #+#             */
/*   Updated: 2023/06/08 08:25:13 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_args(int arg_i, int num, t_data *data)
{
	data->nb_to_eat = 0;
	if (num == 1)
		data->philo_count = arg_i;
	if (num == 2)
		data->time_to_die = arg_i;
	if (num == 3)
		data->time_to_eat = arg_i;
	if (num == 4)
		data->time_to_sleep = arg_i;
	if (num == 5)
		data->nb_to_eat = arg_i;
	return (0);
}

int	check_validity(int c, int argc, char **argv)
{
	int	arg_i;
	int	i;

	i = 1;
	if (c == 1)
		return (1);
	while (i < argc)
	{
		arg_i = ft_atoi(argv[i]);
		if (arg_i == -1)
			return (1);
		if (i == 1 && (arg_i < 0 | arg_i > 210))
			return (1);
		if ((i == 2 || i == 3 || i == 4) && arg_i < 60)
			return (1);
		if (i == 5 && arg_i == 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_input(int argc, char **argv)
{
	int	check;
	int	i;

	check = 0;
	i = 1;
	while (i < argc)
	{
		check = is_negative(argv[i], check);
		check = is_num(argv[i], check);
		if (check != 0)
			return (1);
		i++;
	}
	return (check);
}
