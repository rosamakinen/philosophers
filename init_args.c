/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:30:10 by rmakinen          #+#    #+#             */
/*   Updated: 2023/05/24 06:59:47 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_args(int arg_i, int num, t_data *data)
{
	printf("arg_i : %i \n", arg_i);
	data->nb_to_eat = 0;
	if (num == 1) // NUMBER OF PHILOSOPHERS
		data->philo_count = arg_i;
	if (num == 2) // TIME TO DIE
		data->time_to_die = arg_i;
	if (num == 3) // TIME TO EAT
		data->time_to_eat = arg_i;
	if (num == 4) // TIME TO SLEEP
		data->time_to_sleep = arg_i;
	if (num == 5) // TIMES TO EAT
		data->nb_to_eat = arg_i;
	printf("data->philo_count = %i\n", data->philo_count);
	printf("data->time_to_die = %lli\n", data->time_to_die);
	return (0);
}

int	check_validity(char *arg, int num, t_data *data)
{
	int	arg_i;

	//printf("num in check: %i\n", num);
	arg_i = ft_atoi(arg);
	if (arg_i == -1)
		exit (1);
	if (num == 1 && (arg_i < 0 | arg_i > 210))
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

	//printf("check check: %i\n", check); //PRINTING
	check = is_negative(arg, check);
	//printf("check neg: %i\n", check); //PRINTING
	check = is_num(arg, check);
	//printf("check num: %i\n", check); //PRINTING
	if (check != 0)
		exit (1); //ERROR & EXIT!!
	return (check);
}
