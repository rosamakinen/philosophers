/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:07:57 by rmakinen          #+#    #+#             */
/*   Updated: 2023/05/31 14:50:29 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_philo *philo, t_mcrosec time_to_eat)
{
	pthread_mutex_lock(&philo->data->checking);
	if (philo->data->stop_simulation != 0)
	{
		pthread_mutex_unlock(&philo->data->checking);
		return (-1);
	}
	pthread_mutex_unlock(&philo->data->checking);
	print_message(philo, "is thinking");
	if (philo->id == 0)
		philo_wait(philo->data->time_to_eat / 2);
	grab_forks(philo);
	// if (grab_forks(philo) == -1)
	// {
		// printf("grab_forks returned -1\n");
		// printf("time_to_die = %lli\n", philo->data->time_to_die);
		// philo_wait(philo->data->time_to_die);
		// monitoring(philo->data);
		// return (-1);

	// }
	pthread_mutex_lock(&philo->eating);
	print_message(philo, "is eating");
	pthread_mutex_lock(&philo->data->checking);
	philo->last_meal = get_the_time();
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->data->checking);
	//printf("eating : last meal for %i at %lli\n", philo->id, philo->last_meal);
	printf("times eaten: %i for %i\n", philo->times_eaten, philo->id);
	pthread_mutex_unlock(&philo->eating);
	philo_wait(time_to_eat);
	release_forks(philo);
	sleeping(philo);
	return (0);
}

int	grab_forks(t_philo *philo)
{
	// if (philo->id % 2 == 0)
	// {
		if (pthread_mutex_lock(philo->right))
			return (-1);
		else
			print_message(philo, "has taken fork");
		if (pthread_mutex_lock(philo->left))
			return (-1);
		else
			print_message(philo, "has taken fork");
		if (philo->left == philo->right)
		{
			pthread_mutex_unlock(philo->left);
			return (-1);
		}
	// }
	// else
	// {
	// 	pthread_mutex_lock(philo->left);
	// 	print_message(philo, "has taken fork");
	// 	pthread_mutex_lock(philo->right);
	// 	print_message(philo, "has taken fork");
	// }
	return (0);
}

int	release_forks(t_philo *philo)
{
	// 	if (philo->id % 2 == 0)
	// {
		pthread_mutex_unlock(philo->left);
		print_message(philo, "gave up fork"); //REMOVE
		pthread_mutex_unlock(philo->right);
		print_message(philo, "gave up fork"); //REMOVE

	// }
	// else
	// {
	// 	pthread_mutex_unlock(philo->right);
	// 	print_message(philo, "gave up fork");//REMOVE
	// 	pthread_mutex_unlock(philo->left);
	// 	print_message(philo, "gave up fork");//REMOVE
	// }
	return (0);
}

void	sleeping(t_philo *philo)
{
	//pthread_mutex_lock(&philo->data->sleeping);
	print_message(philo, "is sleeping");
	philo_wait(philo->data->time_to_sleep);
	//pthread_mutex_lock(&philo->data->sleeping);
	eating(philo, philo->data->time_to_eat);
}

// void	thinking(t_philo *philo)
// {
// 	print_message(philo, "is thinking");
// 	philo_wait(philo->data->time_to_sleep);
// 	sleeping(philo);
// }

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
		// print_message(philo, "is thinking");
		philo_wait(temp->data->time_to_eat);
	}
	if (eating(temp, temp->data->time_to_eat) == -1)
	{
		printf("we return back to here??");
		return (NULL);
	}
	return (0);
}
