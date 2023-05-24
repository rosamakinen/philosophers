/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:28:03 by rmakinen          #+#    #+#             */
/*   Updated: 2023/05/24 14:36:24 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	terminate_threads(t_data *data)
{
	static int	i;

	i = 0;
	//printf("test666\n");
	while (i < data->philo_count)
	{
		//printf("test2\n");
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
}

int	monitoring(t_data *data)
{
	int	i;
	long long	starv_check;
	i = 0;
	while (i < data->philo_count)
	{
		starv_check = get_the_time() - data->philo[i].last_meal;
		// printf("starv_check = %lli\n", starv_check);
		// printf("time to die = %lli\n", data->time_to_die);
		if (data->stop_simulation != 0)
		{
			//printf("going to terminate\n");
			terminate_threads(data);
			destroy_free(data);
		}
		if (starv_check >= data->time_to_die)
		{
			print_message(data->philo, "has died");
			//printf("stop simu = %i\n", data->stop_simulation);
			data->stop_simulation = -1;
			//printf("stop simu = %i\n", data->stop_simulation);
		}
		//printf("times eaten: %i for %i\n", data->philo[i].times_eaten, data->philo[i].id);
		if (data->nb_to_eat > 0)
			if (data->philo[i].times_eaten >= data->nb_to_eat)
				data->stop_simulation = -1;
		usleep(500);
		i++;
	}
	return (0);
}
