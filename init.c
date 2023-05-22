/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 07:53:23 by rmakinen          #+#    #+#             */
/*   Updated: 2023/05/22 11:16:15 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int	init_mutexes(t_data *data)
{
	int i;

	i = 0;
	printf("initializing mutexes\n");
	data->fork_lock = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	while(i < data->philo_count)
	{
		pthread_mutex_init(&data->fork_lock[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->eating, NULL);
	pthread_mutex_init(&data->printing, NULL);
	pthread_mutex_init(&data->routine, NULL);
	pthread_mutex_init(&data->sleeping, NULL);
	printf("did that\n");
	return (0);
}

t_philo *init_philos(t_data *data)
{
	int		i;
	t_philo	*temp_philo;
	t_philo	*temp;

	i = 0;
	temp_philo = ft_calloc(data->philo_count, sizeof(t_philo));
	if (!temp_philo)
		return (NULL);
	printf("initializing philos\n");
	while (i < data->philo_count)
	{
		temp_philo[i].data = data;
		temp_philo[i].id = i + 1;
		temp_philo[i].times_eaten = 0;
		i++;
	}
	printf("did that too\n");
	temp = temp_philo;
	return (temp);
}

t_data	*init_data(int argc, char **argv)
{
	t_data *data;
	int		i;

	i = 1;
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	printf("initializing data\n");
	while (i < argc)
	{
		check_input(argv[i]);
		check_validity(argv[i], i, data);
		i++;
	}
	init_mutexes(data);
	data->stop_simulation = 0;
	data->philo = init_philos(data);
	if (!data->philo)
		return (NULL);
	printf("did that\n");
	return (data);
}
