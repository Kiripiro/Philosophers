/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atourret <atourret@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 10:42:28 by atourret          #+#    #+#             */
/*   Updated: 2021/08/22 11:50:53 by atourret         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	ft_bzero(void *s, size_t n)
{
	int		i;
	char	*str;

	i = 0;
	str = s;
	while (n-- > 0)
		str[i++] = 0;
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_check_str(const char *str, int i)
{
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	while (str[i] == '+')
		i++;
	if (ft_check_str(str, i) == -1)
		return (-1);
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		res = res * 10 + str[i++] - 48;
	return (res);
}

int	parsing(int ac, char **av, t_main *main)
{
	main->data.nb_philo = ft_atoi(av[1]);
	main->data.time_to_die = ft_atoi(av[2]);
	main->data.time_to_eat = ft_atoi(av[3]);
	main->data.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		main->data.philo_must_eat = ft_atoi(av[5]);
		if (main->data.philo_must_eat <= 0)
		{
			printf("Number_of_times_each_philosopher_must_eat should be > 0\n");
			return (-1);
		}
	}
	if (main->data.nb_philo <= 0)
	{
		printf("Number of philosophers should be > 1\n");
		return (-1);
	}
	if (main->data.time_to_die < 60 || main->data.time_to_eat < 60
		|| main->data.time_to_sleep < 60)
	{
		printf("Time error\n");
		return (-1);
	}
	return (1);
}