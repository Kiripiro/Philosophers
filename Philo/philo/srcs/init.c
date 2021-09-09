/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atourret <atourret@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 11:45:31 by atourret          #+#    #+#             */
/*   Updated: 2021/09/08 14:11:56 by atourret         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

t_philo	init_philo(t_main *main, int id)
{
	t_philo	philo;

	philo.main = main;
	philo.id = id;
	philo.alive = 1;
	philo.sleep = 0;
	philo.eat = 0;
	philo.think = 0;
	philo.nb_ate = 0;
	philo.main->stop = 0;
	pthread_mutex_init(&philo.fork, NULL);
	return (philo);
}

int	initialization(t_main *main)
{
	pthread_t	*threads;
	t_philo		*philo;
	int			i;

	philo = malloc(sizeof(t_philo) * main->data.nb_philo);
	if (!philo)
		return (-1);
	i = -1;
	while (++i < main->data.nb_philo)
	{
		philo[i] = init_philo(main, i + 1);
		if (i != 0)
			philo[i].prev_fork = &philo[i - 1].fork;
	}
	threads = malloc(sizeof(pthread_t) * main->data.nb_philo);
	if (!threads)
	{
		quit(philo, threads, 0);
		return (-1);
	}
	pthread_mutex_init(&main->write, NULL);
	pthread_mutex_init(&main->meal_check, NULL);
	start_simulation(main, philo, threads);
	return (1);
}