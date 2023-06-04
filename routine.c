/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:07:57 by rmakinen          #+#    #+#             */
/*   Updated: 2023/06/03 16:46:47 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_philo *philo, t_mcrosec time_to_eat)
{
	if (check_flag(philo->data, 0))
	{
		return (0);
	}
	print_message(philo, "is thinking");
	pthread_mutex_lock(philo->left);
	print_message(philo, "has taken fork");
	pthread_mutex_lock(philo->right);
	print_message(philo, "has taken fork");
	print_message(philo, "is eating");
	philo->times_eaten++;
	philo->last_meal = get_the_time();
	philo_wait(time_to_eat);
	pthread_mutex_unlock(philo->right);
	print_message(philo, "gave up fork");
	pthread_mutex_unlock(philo->left);
	print_message(philo, "gave up fork");
	sleeping(philo);
	return (0);
}
int	sleeping(t_philo *philo)
{
	if (check_flag(philo->data, 0))
	{
		//terminate_threads(philo->data);
		return (1);
	}
	print_message(philo, "is sleeping");
	philo_wait(philo->data->time_to_sleep);
	eating(philo, philo->data->time_to_eat);
	return (0);
}

void	*routine(void *philo)
{
	int	i;
	t_philo	*temp;

	i = 0;
	temp = (t_philo *)philo;
	pthread_mutex_lock(&temp->data->routine);
	pthread_mutex_unlock(&temp->data->routine);
	if (temp->id % 2 != 0)
	{
		philo_wait(temp->data->time_to_eat);
	}
	if (eating(temp, temp->data->time_to_eat) == 0)
	{
		return (NULL);
	}
	return (NULL);
}
