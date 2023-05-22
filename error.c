/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:36:40 by rmakinen          #+#    #+#             */
/*   Updated: 2023/05/22 11:20:28 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_and_free(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	pthread_mutex_destroy(data->fork_lock);
	free(data->fork_lock);
	pthread_mutex_destroy(&data->routine);
	pthread_mutex_destroy(&data->eating);
	pthread_mutex_destroy(&data->printing);
	pthread_mutex_destroy(&data->sleeping);
	exit (0);
}
