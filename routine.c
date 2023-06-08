/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:07:57 by rmakinen          #+#    #+#             */
/*   Updated: 2023/06/08 08:01:32 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_philo *philo, long long time_to_eat)
{
	if (check_flag(philo->data, 0))
		return (1);
	if (philo->data->philo_count == 1)
	{
		eating_alone(philo);
		return (0);
	}
	take_forks(philo);
	pthread_mutex_lock(&philo->eating);
	philo->times_eaten++;
	philo->last_meal = get_the_time();
	pthread_mutex_unlock(&philo->eating);
	print_message(philo, "is eating");
	philo_wait(philo->data, time_to_eat);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	if (sleeping(philo))
		return (1);
	return (0);
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	print_message(philo, "has taken fork");
	pthread_mutex_lock(philo->right);
	print_message(philo, "has taken fork");
	if (philo->left == philo->right)
		return (1);
	return (0);
}

int	eating_alone(t_philo *philo)
{
	pthread_mutex_lock(philo->right);
	print_message(philo, "has taken fork");
	philo_wait(philo->data, philo->data->time_to_die);
	return (0);
}

int	sleeping(t_philo *philo)
{
	if (check_flag(philo->data, 0))
		return (1);
	print_message(philo, "is sleeping");
	philo_wait(philo->data, philo->data->time_to_sleep);
	print_message(philo, "is thinking");
	if (eating(philo, philo->data->time_to_eat))
		return (1);
	return (0);
}

void	*routine(void *philo)
{
	int		i;
	t_philo	*temp;

	i = 0;
	temp = (t_philo *)philo;
	pthread_mutex_lock(&temp->data->routine);
	pthread_mutex_unlock(&temp->data->routine);
	if (temp->id % 2 != 0)
	{
		if (temp->data->philo_count >= 100)
			philo_wait(temp->data, 3);
		else
			philo_wait(temp->data, 7);
	}
	print_message(temp, "is thinking");
	if (eating(temp, temp->data->time_to_eat) == 0)
	{
		return (NULL);
	}
	return (NULL);
}
