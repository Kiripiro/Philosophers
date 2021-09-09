/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atourret <atourret@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 13:12:14 by atourret          #+#    #+#             */
/*   Updated: 2021/08/26 13:37:26 by atourret         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	ft_take_fork(t_philo *philo)
{
	if (!philo->id % 2)
	{
		pthread_mutex_lock(&philo->fork);
		if (philo->alive && !philo->main->stop)
			display_action(philo, TAKE);
		pthread_mutex_lock(philo->prev_fork);
		if (philo->alive && !philo->main->stop)
			display_action(philo, TAKE);
	}
	else
	{
		pthread_mutex_lock(philo->prev_fork);
		if (philo->alive && !philo->main->stop)
			display_action(philo, TAKE);
		pthread_mutex_lock(&philo->fork);
		if (philo->alive && !philo->main->stop)
			display_action(philo, TAKE);
	}
}

void	ft_drop_fork(t_philo *philo)
{
	if (!philo->id % 2)
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(philo->prev_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->prev_fork);
		pthread_mutex_unlock(&philo->fork);
	}
}
