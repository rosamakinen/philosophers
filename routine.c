/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:07:57 by rmakinen          #+#    #+#             */
/*   Updated: 2023/05/22 15:01:11 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo, t_mcrosec time_to_eat)
{
	pthread_mutex_lock(&philo->data->eating);
	printf("%i is eating\n", philo->id);
	philo_wait(time_to_eat);
	philo->last_meal = get_the_time();
	pthread_mutex_unlock(&philo->data->eating);

}

// void	sleeping(t_philo *philo, t_mcrosec time_to_eat)
// {
// 	pthread_mutex_lock(&philo->data->sleeping);
// 	printf("%i is sleeping\n", philo->id);
// 	time_to_eat = 0;
// 	pthread_mutex_lock(&philo->data->sleeping);
// }

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
		philo_wait(temp->data->time_to_eat);
	eating(temp, temp->data->time_to_eat);
	return (0);
}
