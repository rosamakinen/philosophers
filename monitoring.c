/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:28:03 by rmakinen          #+#    #+#             */
/*   Updated: 2023/06/08 07:57:53 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_flag(t_data *data, int flag)
{
	pthread_mutex_lock(&data->checking);
	if (flag == 1)
	{
		data->exit_flag = 1;
		pthread_mutex_unlock(&data->checking);
		return (1);
	}
	if (data->exit_flag == 1)
	{
		pthread_mutex_unlock(&data->checking);
		return (1);
	}
	pthread_mutex_unlock(&data->checking);
	return (0);
}

int	check_if_dead(t_philo *philo)
{
	long long	time;

	time = (get_the_time() - philo->data->time_to_die);
	if (philo->data->nb_to_eat > 0)
	{
		if (philo->data->all_eaten >= philo->data->philo_count)
		{
			check_flag(philo->data, 1);
			return (1);
		}
		pthread_mutex_lock(&philo->eating);
		if (philo->times_eaten >= philo->data->nb_to_eat && philo->flag == 0)
		{
			philo->data->all_eaten++;
			philo->flag = 1;
		}
		pthread_mutex_unlock(&philo->eating);
	}
	pthread_mutex_lock(&philo->eating);
	if (get_the_time() - philo->last_meal >= \
	philo->data->time_to_die + philo->data->buffer)
		if (check_last_meal(philo) == 1)
			return (1);
	pthread_mutex_unlock(&philo->eating);
	return (0);
}

int	check_last_meal(t_philo *philo)
{
	print_message(philo, "has died");
	check_flag(philo->data, 1);
	pthread_mutex_unlock(&philo->eating);
	return (1);
}

int	monitoring(t_data *data)
{
	int	keep_going;
	int	i;

	keep_going = 1;
	while (keep_going)
	{
		i = 0;
		while (i < data->philo_count)
		{
			if (check_if_dead(&data->philo[i]) == 1)
			{
				keep_going = 0;
			}
			i++;
		}
		if (data->philo_count > 150)
			philo_wait(data, 1);
		else
			usleep(250);
	}
	return (0);
}
