/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:36:40 by rmakinen          #+#    #+#             */
/*   Updated: 2023/06/07 16:00:53 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_free(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_join(data->philo[i].thread, NULL))
			break ;
		i++;
	}
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->fork_lock[i]);
		pthread_mutex_destroy(&data->philo[i].eating);
		i++;
	}
	pthread_mutex_destroy(data->fork_lock);
	pthread_mutex_destroy(&data->routine);
	pthread_mutex_destroy(&data->printing);
	free(data->fork_lock);
	free(data->philo);
	free(data);
	return (0);
}
