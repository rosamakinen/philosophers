/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 08:21:30 by rmakinen          #+#    #+#             */
/*   Updated: 2023/05/24 14:47:56 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *message)
{
	t_mcrosec	current_time;
	if (philo->data->stop_simulation != 0)
		return ;
	pthread_mutex_lock(&philo->data->printing);
	current_time = get_the_time();
	current_time = current_time - philo->data->starting_time;
	if (strcmp(message, "has died") == 0)
		printf(RED"%llu, id %i, %s\n", current_time, philo->id, message);
	if (strcmp(message, "has taken fork") == 0)
		printf(CYAN"%llu, id %i, %s\n", current_time, philo->id, message);
	if (strcmp(message, "gave up fork") == 0 || strcmp(message, "took left fork") == 0)
		printf(CYAN"%llu, id %i, %s\n", current_time, philo->id, message);
	if (strcmp(message, "is eating") == 0)
		printf(GREEN"%llu, id %i, %s\n", current_time, philo->id, message);
	if (strcmp(message, "is sleeping") == 0 || strcmp(message, "is thinking") == 0)
		printf(PURPLE"%llu, id %i, %s\n", current_time, philo->id, message);
	//printf("left no: %i, right no: %i\n", philo->id - 1, philo->id);
	pthread_mutex_unlock(&philo->data->printing);
}

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
		printf("created thread for philo id %i\n", i);
		if (pthread_create(&data->philo[i].thread, NULL, &routine, &data->philo[i]) != 0)
			return (1);
		data->philo[i].last_meal = get_the_time();
		i++;
	}
	data->starting_time = get_the_time();
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
	start_routine(data);
	while (1)
	{
		monitoring(data);
			//break;
		// if (data->stop_simulation != 0)
	}
	terminate_threads(data);
	return (0);
}
