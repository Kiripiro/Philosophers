/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atourret <atourret@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 10:11:27 by atourret          #+#    #+#             */
/*   Updated: 2021/08/26 13:39:24 by atourret         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	display_action(t_philo *philo, int action)
{
	pthread_mutex_lock(&philo->main->write);
	printf("%ld ms :%d",
		(ft_get_time() - philo->main->first_time), philo->id);
	if (action == DIED)
		printf(" died\n");
	else if (action == SLEEP)
		printf(" is sleeping\n");
	else if (action == THINK)
		printf(" is thinking\n");
	else if (action == EAT)
		printf(" is eating\n");
	else if (action == TAKE)
		printf(" has taken fork\n");
	pthread_mutex_unlock(&philo->main->write);
}

void	ft_eat(t_philo *philo)
{
	ft_take_fork(philo);
	if (philo->alive)
	{
		display_action(philo, EAT);
		pthread_mutex_lock(&philo->main->meal_check);
		philo->last_time = ft_get_time() - philo->main->first_time;
		pthread_mutex_unlock(&philo->main->meal_check);
		philo->eat = 1;
		philo->sleep = 0;
		philo->nb_ate++;
		better_usleep(philo->main->data.time_to_eat, philo);
	}
	ft_drop_fork(philo);
}

void	ft_sleep(t_philo *philo)
{
	display_action(philo, SLEEP);
	better_usleep(philo->main->data.time_to_sleep, philo);
	philo->think = 0;
	philo->sleep = 1;
}

void	ft_think(t_philo *philo)
{
	display_action(philo, THINK);
	philo->think = 1;
	philo->eat = 0;
}

void	ft_die(t_philo *philo)
{
	if (!philo->main->stop)
	{
		display_action(philo, DIED);
		philo->alive = 0;
		if (!philo->main->data.philo_must_eat)
			philo->main->stop = 1;
	}
}
