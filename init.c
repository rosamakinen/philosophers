/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 07:53:23 by rmakinen          #+#    #+#             */
/*   Updated: 2023/06/08 14:25:40 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	data->fork_lock = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->fork_lock)
		return (1);
	while (i < data->philo_count)
	{
		pthread_mutex_init(&data->fork_lock[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->printing, NULL);
	pthread_mutex_init(&data->routine, NULL);
	pthread_mutex_init(&data->checking, NULL);
	return (0);
}

t_philo	*init_philos(t_data *data)
{
	int		i;
	int		t;
	t_philo	*temp_philo;

	i = 0;
	t = data->philo_count;
	temp_philo = ft_calloc(data->philo_count, sizeof(t_philo));
	if (!temp_philo)
		return (NULL);
	while (i < data->philo_count)
	{
		pthread_mutex_init(&temp_philo[i].eating, NULL);
		temp_philo[i].data = data;
		temp_philo[i].id = i + 1;
		temp_philo[i].times_eaten = 0;
		temp_philo[i].flag = 0;
		if (i == 0)
			temp_philo[i].left = &temp_philo->data->fork_lock[t - 1];
		else
			temp_philo[i].left = &temp_philo->data->fork_lock[i - 1];
		temp_philo[i].right = &temp_philo->data->fork_lock[i];
		i++;
	}
	return (temp_philo);
}

t_data	*init_data(int argc, char **argv)
{
	t_data	*data;
	int		i;
	int		arg_i;

	i = 1;
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	while (i < argc)
	{
		arg_i = ft_atoi(argv[i]);
		init_args(arg_i, i, data);
		i++;
	}
	init_mutexes(data);
	data->exit_flag = 0;
	data->all_eaten = 0;
	data->buffer = 0;
	// if ((data->philo_count > 10 && data->time_to_die < 200) \
	// || data->time_to_die < data->time_to_eat)
	if ((data->philo_count < 100 && data->time_to_die <= 110) \
	|| (data->philo_count >= 100 && (data->time_to_die <= data->time_to_eat)))
		data->buffer = 2;
	data->philo = init_philos(data);
	if (!data->philo)
		return (NULL);
	return (data);
}
