/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:36:40 by rmakinen          #+#    #+#             */
/*   Updated: 2023/05/26 10:40:48 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_free(t_data *data)
{
	int	i;

	i = 0;
	printf("in destroy free\n");
	//printf("times eaten: %i for %i\n", data->philo->times_eaten, data->philo->id);
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->fork_lock[i]);
		pthread_mutex_destroy(&data->philo[i].eating);
		i++;
	}
	pthread_mutex_destroy(data->fork_lock);
	free(data->fork_lock);
	pthread_mutex_destroy(&data->routine);
	pthread_mutex_destroy(&data->printing);
	pthread_mutex_destroy(&data->sleeping);
	exit (0);
}
