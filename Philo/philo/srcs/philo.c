/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atourret <atourret@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 13:13:17 by atourret          #+#    #+#             */
/*   Updated: 2021/09/07 16:04:03 by atourret         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	check_death(t_main *main, t_philo *philo, pthread_t *threads)
{
	int			i;
	long int	check;

	while (philo->alive && !philo->main->stop)
	{
		i = 0;
		if (philo->main->data.philo_must_eat
			&& philo->nb_ate == philo->main->data.philo_must_eat)
			break ;
		while (i < philo->main->data.nb_philo)
		{
			pthread_mutex_lock(&main->meal_check);
			check = (ft_get_time() - main->first_time) - philo[i].last_time;
			if (check > main->data.time_to_die)
			{
				ft_die(&philo[i]);
				pthread_mutex_unlock(&main->meal_check);
				quit(philo, threads, 1);
				return (-1);
			}
			pthread_mutex_unlock(&main->meal_check);
			i++;
		}
	}
	return (0);
}

void	start_simulation(t_main *main, t_philo *philo, pthread_t *threads)
{
	int	i;

	i = -1;

	main->first_time = ft_get_time();
	while (++i != main->data.nb_philo)
	{
		if (pthread_create(&threads[i], NULL, run_simulation, &philo[i]))
			philo->main->stop = 1;
	}
	if (check_death(main, philo, threads) == -1)
		return ;
	if (philo->alive && !philo->main->stop)
	{
		i = -1;
		while (++i != main->data.nb_philo)
			pthread_join(threads[i], NULL);
	}
	quit(philo, threads, 1);
}

void	*run_simulation(void *data)
{
	t_philo	*philo;

	philo = data;
	if (philo->id % 2)
		usleep(1500);
	while (philo->alive && !philo->main->stop)
	{
		if (!philo->main->stop && philo->alive && !philo->eat)
			ft_eat(philo);
		if (!philo->main->stop && philo->alive && !philo->sleep)
			ft_sleep(philo);
		if (philo->alive && philo->main->data.philo_must_eat \
			&& philo->nb_ate == philo->main->data.philo_must_eat)
			break ;
		if (!philo->main->stop && philo->alive && !philo->think)
			ft_think(philo);
	}
	return (data);
}