/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:30:10 by rmakinen          #+#    #+#             */
/*   Updated: 2023/06/06 14:53:56 by rmakinen         ###   ########.fr       */
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

int	check_validity(char *arg, int num, t_data *data)
{
	int	arg_i;

	arg_i = ft_atoi(arg);
	if (arg_i == -1)
		exit (1);
	if (num == 1 && (arg_i < 0 | arg_i > 210))
		exit (1);
	if ((num == 2 || num == 3) && arg_i < 60)
		exit (1);
	if (num == 5 && arg_i == 0)
		exit (1);
	else
		init_args(arg_i, num, data);
	return (0);
}

int	check_input(char *arg)
{
	int	check;

	check = 0;
	check = is_negative(arg, check);
	check = is_num(arg, check);
	if (check != 0)
		exit (1);
	return (check);
}
