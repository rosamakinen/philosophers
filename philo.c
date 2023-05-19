/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 08:21:30 by rmakinen          #+#    #+#             */
/*   Updated: 2023/05/18 14:11:35 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo)
{
	t_philo *temp;
	
	temp = (t_philo *)philo;
	pthread_mutex_lock(&temp->data->routine);
	printf("first philo here: %i\n", temp->id);
	pthread_mutex_unlock(&temp->data->routine);
	printf("whatever is the routine\n philo id: %i\n", temp->id);
	return (0);
}

int	start_routine(t_data *data)
{
	int i;

	i = 0;
	pthread_mutex_lock(&data->routine);
	while (i < data->philo_count)
	{
		printf("created thread for philo id %i\n", i + 1);
		pthread_create(&data->philo[i].thread, NULL, &routine, &data->philo[i]);
		i++;
	}
	data->starting_time = get_time();
	pthread_mutex_unlock(&data->routine);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (argc != 5 && argc != 6)
		exit (1);
	data = init_data(argc, argv);
	if (!data)
	{
		printf("something went wrong with initializaltion\n");
		exit (1);
	}
	printf("yes?\n");
	start_routine(data);
	printf("yes?\n");
	return (0);
}
