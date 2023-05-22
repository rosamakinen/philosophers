/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 08:21:30 by rmakinen          #+#    #+#             */
/*   Updated: 2023/05/22 15:01:42 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_the_time()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	philo_wait(t_mcrosec to_sleep)
{
	t_mcrosec	time;

	time = get_the_time();
	while (time + to_sleep > get_the_time())
		usleep(500);
}

int	start_routine(t_data *data)
{
	int i;

	i = 0;
	pthread_mutex_lock(&data->routine);
	while (i < data->philo_count)
	{
		printf("created thread for philo id %i\n", i + 1);
		if (pthread_create(&data->philo[i].thread, NULL, &routine, &data->philo[i]) != 0)
			return (1);
		i++;
	}
	data->starting_time = get_the_time();
	printf("THE TIME IS : %lli", data->starting_time);
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
	//if (data->stop_simulation != 0)
	join_and_free(data);
	printf("yes?\n");
	return (0);
}
