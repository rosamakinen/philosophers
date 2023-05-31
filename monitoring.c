/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:28:03 by rmakinen          #+#    #+#             */
/*   Updated: 2023/05/31 16:17:11 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	terminate_threads(t_data *data)
{
	static int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
}

int	monitoring(t_data *data)
{
	int	i;
	int	keep_going;

	keep_going = 1;
	while (keep_going == 1)
	{
		i = 0;
		while (i < data->philo_count)
		{
			if (data->stop_simulation != 0)
			{
				terminate_threads(data);
				destroy_free(data);
			}
			if (starved(data))
			{
				keep_going = 0;
			}
			if (eaten_enough(data))
			{
				keep_going = 0;
			}
		i++;
		}
		usleep(500);
	}
	return (0);
}

int	starved(t_data *data)
{
		long long	starv_check;
		long long	double_check;

		pthread_mutex_lock(&data->finish);
		double_check = get_the_time();
		pthread_mutex_lock(&data->checking);
		starv_check = (get_the_time() - data->philo->last_meal);
		if (starv_check >= data->time_to_die)
		{
			print_message(data->philo, "has died");
			data->stop_simulation = -1;
			return (1);
		}
		pthread_mutex_unlock(&data->checking);
		pthread_mutex_unlock(&data->finish);

	return (0);
}

int	eaten_enough(t_data *data)
{

	if (data->nb_to_eat > 0)
	{
		pthread_mutex_lock(&data->philo->eating);
		if (data->philo->times_eaten >= data->nb_to_eat)
		{
			//printf("all eaten count: %i\n", data->all_eaten);
			if (data->philo->flag == 0)
			{
				data->all_eaten++;
				printf("***all eaten count: %i***\n", data->all_eaten);
				data->philo->flag = 1;
			}
		}
		if (data->all_eaten >= data->nb_to_eat)
		{

			//printf("all_eaten = %d, nb_to_eat = %d\n", data->all_eaten, data->nb_to_eat);
			pthread_mutex_lock(&data->checking);
			data->stop_simulation = -1;
			pthread_mutex_unlock(&data->checking);
			return (1);
		}
		pthread_mutex_unlock(&data->philo->eating);
	}
	return (0);
}

