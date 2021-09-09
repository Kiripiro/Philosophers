/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atourret <atourret@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 10:28:19 by atourret          #+#    #+#             */
/*   Updated: 2021/09/07 16:05:41 by atourret         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	main(int ac, char **av)
{
	t_main	main;

	if (ac != 5 && ac != 6)
	{
		printf("Use this format [./philo] [number_of_philosophers] [time_to_die]");
		printf("[time_to_eat] [time_to_sleep] [option]\n");
		printf("\n	Example = ./philo 5 800 200 200\n");
		printf("\nOption = number_of_times_each_philosopher_must_eat\n");
		printf("\n	Example = ./philo 5 800 200 200 5\n");
		return (-1);
	}
	ft_bzero(&main, sizeof(t_main));
	if (!parsing(ac, av, &main))
		return (-1);
	if (!initialization(&main))
		return (-1);
	return (0);
}