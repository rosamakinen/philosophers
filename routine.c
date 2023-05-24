/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:07:57 by rmakinen          #+#    #+#             */
/*   Updated: 2023/05/24 14:48:48 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo, t_mcrosec time_to_eat)
{
	//grab_forks(philo);
	pthread_mutex_lock(&philo->data->eating);
	philo->last_meal = get_the_time();
	print_message(philo, "is eating");
	philo_wait(time_to_eat);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->data->eating);
	release_forks(philo);
	thinking(philo);
}

void	grab_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right);
		print_message(philo, "has taken fork");
		pthread_mutex_lock(philo->left);
		print_message(philo, "has taken fork");
	}
	else
	{
		pthread_mutex_lock(philo->left);
		print_message(philo, "has taken fork");
		pthread_mutex_lock(philo->right);
		print_message(philo, "has taken fork");
	}
	eating(philo, philo->data->time_to_eat);
}

void	release_forks(t_philo *philo)
{
		if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		print_message(philo, "gave up fork");

	}
	else
	{
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(philo->left);
		print_message(philo, "gave up fork");
	}
}

void	sleeping(t_philo *philo)
{
	//pthread_mutex_lock(&philo->data->sleeping);
	print_message(philo, "is sleeping");
	philo_wait(philo->data->time_to_sleep);
	//pthread_mutex_lock(&philo->data->sleeping);
	eating(philo, philo->data->time_to_eat);
}

void	thinking(t_philo *philo)
{
	print_message(philo, "is thinking");
	philo_wait(philo->data->time_to_sleep);
	sleeping(philo);
}

void	*routine(void *philo)
{
	int	i;
	t_philo	*temp;

	i = 0;
	temp = (t_philo *)philo;
	pthread_mutex_lock(&temp->data->routine);
	pthread_mutex_unlock(&temp->data->routine);
//	printf("**whatever is the routine with philo id: %i**\n", temp->id);
	if (temp->id % 2 == 0)
	{
		philo_wait(temp->data->time_to_eat);
	}
	grab_forks(temp);
	//eating(temp, temp->data->time_to_eat);
	return (0);
}
