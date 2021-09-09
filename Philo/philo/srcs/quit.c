/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atourret <atourret@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 15:51:31 by atourret          #+#    #+#             */
/*   Updated: 2021/09/07 16:17:03 by atourret         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	quit(t_philo *philo, pthread_t *threads, int j)
{
	int	i;

	i = -1;
	while (++i != philo->main->data.nb_philo)
		pthread_mutex_destroy(&philo[i].fork);
	if (j == 1)
	{
		free(threads);
		pthread_mutex_destroy(&philo->main->write);
		pthread_mutex_destroy(&philo->main->meal_check);
	}
	free(philo);
}