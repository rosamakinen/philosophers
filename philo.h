/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:51:01 by rmakinen          #+#    #+#             */
/*   Updated: 2023/05/15 13:52:35 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h> //FOR PRINTF! REMOVE!
#include <stdlib.h>
#include <unistd.h>
int	check_input(char *arg);
int	is_num(char *arg, int check);
int	ft_strlen(char *str);

#endif
