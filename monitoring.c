/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:28:03 by rmakinen          #+#    #+#             */
/*   Updated: 2023/06/03 16:51:58 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_flag(t_data *data, int flag)
{
	if (flag == 1)
	{
		data->exit_flag = 1;
		return (1);
	}
	if (data->exit_flag == 1)
	{
		return (1);
	}
	return (0);
}

int	check_if_dead(t_philo *philo)
{
	t_mcrosec time;

	time = (get_the_time() - philo->data->time_to_die);
	if (philo->data->nb_to_eat > 0)
	{
		if (philo->data->all_eaten >= philo->data->nb_to_eat)
		{
			check_flag(philo->data, 1);
			printf("OHMYGODSSS\n");
			return (1);
		}
		if (philo->times_eaten >= philo->data->nb_to_eat &&
		philo->data->philo->flag == 0)
		{
			philo->data->all_eaten++;
			philo->data->philo->flag = 1;
		}
	}
	if (time >= philo->last_meal)
	{
		check_flag(philo->data, 1);
		print_message(philo, "has died");
		return (1);
	}
	return (0);
}

int	monitoring(t_data *data)
{
	int	keep_going;
	int i;


	keep_going = 1;
	while (keep_going)
	{
		i = 0;
		while (i < data->philo_count)
		{
			if (check_if_dead(&data->philo[i]) == 1)
				keep_going = 0;
			i++;
		}
	}
	printf("going from monitoring\n");
	destroy_free(data);
	return (0);
}

// void	terminate_threads(t_data *data)
// {
// 	static int	i;

// 	i = 0;
// 	while (i < data->philo_count)
// 	{
// 		printf("terminating threads\n");
// 		pthread_join(data->philo[i].thread, NULL);
// 		i++;
// 	}
// 	destroy_free(data);
// }

int	checker(t_data *data, int flag)
{
	if (flag == 1)
	{
		data->exit_flag = 1;
		return (1);
	}
	if (data->exit_flag == 1)
	{
		return (1);
	}
	return (0);
}

