/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:28:03 by rmakinen          #+#    #+#             */
/*   Updated: 2023/06/04 14:56:22 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_flag(t_data *data, int flag)
{
	if (flag == 1)
	{
		data->exit_flag = 1;
		return (1);
	}
	if (data->exit_flag == 1)
	{
		return (1);
	}
	return (0);
}

int	check_if_dead(t_philo *philo)
{
	t_mcrosec time;

	time = (get_the_time() - philo->data->time_to_die);
	//printf("personal times_eaten %i by %i\n", philo->times_eaten, philo->id);
	if (philo->data->nb_to_eat > 0)
	{
		if (philo->data->all_eaten >= philo->data->philo_count)
		{
			check_flag(philo->data, 1);
			printf("OHMYGODSSS\n");
			return (1);
		}
		//printf("personal times_eaten %i by %i", philo->times_eaten, philo->id);
		if (philo->times_eaten >= philo->data->nb_to_eat && philo->flag == 0)
		{
			printf("all_eaten increased: %i by %i\n", philo->data->all_eaten, philo->id);
			philo->data->all_eaten++;
			philo->flag = 1;
		}
	}
	if (get_the_time() - philo->last_meal >= philo->data->time_to_die)
	{
		print_message(philo, "has died");
		check_flag(philo->data, 1);
		return (1);
	}
	return (0);
}

int	monitoring(t_data *data)
{
	int	keep_going;
	int i;


	keep_going = 1;
	while (keep_going)
	{
		i = 0;
		while (i < data->philo_count)
		{
			//printf("philo id: %i, philo[i]: %i\n", data->philo->id, i);
			if (check_if_dead(&data->philo[i]) == 1)
			{
				keep_going = 0;
				destroy_free(data);
			}
			i++;
			usleep(100);
		}
	}
	printf("going from monitoring\n");
	destroy_free(data);
	return (0);
}

// void	terminate_threads(t_data *data)
// {
// 	static int	i;

// 	i = 0;
// 	while (i < data->philo_count)
// 	{
// 		printf("terminating threads\n");
// 		pthread_join(data->philo[i].thread, NULL);
// 		i++;
// 	}
// 	destroy_free(data);
// }

int	checker(t_data *data, int flag)
{
	if (flag == 1)
	{
		data->exit_flag = 1;
		return (1);
	}
	if (data->exit_flag == 1)
	{
		return (1);
	}
	return (0);
}

