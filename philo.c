/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 08:21:30 by rmakinen          #+#    #+#             */
/*   Updated: 2023/06/06 07:48:36 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_message(t_philo *philo, char *message)
{
	t_mcrosec	event_time;

	if (check_flag(philo->data, 0))
		return (1);
	event_time = get_the_time() - philo->data->starting_time;
	pthread_mutex_lock(&philo->data->checking);
	if (philo->data->exit_flag == 1)
	{
		pthread_mutex_unlock(&philo->data->checking);
		return (1);
	}
	printf("%llu %i %s\n", event_time, philo->id, message);
	pthread_mutex_unlock(&philo->data->checking);
	return (0);
}

long long	get_the_time()
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
	monitoring(data);
	printf("going from main\n");
	destroy_free(data);
	printf("coming from main\n");
	return (0);
}
