/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:24:08 by rmakinen          #+#    #+#             */
/*   Updated: 2023/06/06 07:32:18 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long	i;
	long	symbol;
	long	result;

	i = 0;
	symbol = 1;
	result = 0;
	while (str[i] == '\t' || str[i] == '\v' || str[i] == '\f' || \
	str[i] == '\r' || str[i] == '\n' || str[i] == ' ' || str[i] == '\f')
		i++;
	if (str[i] == '-')
		symbol = -symbol;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		if (result * symbol > 2147483647)
			return (-1);
		if (result * symbol < -2147483648)
			return (-1);
		else
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return ((int)result * (int)symbol);
}

int	is_num(char *arg, int check)
{
	int	i;

	i = 0;
	if (check != 0)
		return (check);
	while (arg[i] != '\0')
	{
		if (arg[i] > 47 && arg[i] < 58)
			i++;
		else
			return (1);
	}
	return (0);
}

int	is_negative(char *arg, int check)
{
	if (check != 0)
		return (check);
	if (arg[0] == '-' || arg[0] == '+')
		return (1);
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return ;
	while (i < n)
	{
		((char *)s)[i] = '\0';
			i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*p;

	if (count == 0 || size == 0)
	{
		p = malloc(1);
		if (p == 0)
			return (0);
		return (p);
	}
	if (count * size / size != count)
		return (0);
	p = malloc(count * size);
	if (p == 0)
		return (0);
	ft_bzero (p, count * size);
	return (p);
}
