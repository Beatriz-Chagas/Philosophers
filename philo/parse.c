/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchagas <bchagas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 06:08:59 by bchagas           #+#    #+#             */
/*   Updated: 2026/02/03 07:38:23 by bchagas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long	ft_atol(char *str)
{
	long	res;
	int		i;
	
	res = 0;
	i = 0;
	while (str[i])
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

int parse_args (int ac, char **av, t_rules *rules)
{
	int	i = 1;
	
	if  (ac < 5 || ac > 6)
		return  (1);
	while (i < ac)
	{
		if (!is_digit(av[i]))
			return (1);
		i++;
	}
	rules->philos = ft_atol(av[1]);
	rules->time_die = ft_atol(av[2]);
	rules->time_eat = ft_atol(av[3]);
	rules->time_sleep = ft_atol(av[4]);
	if (ac == 6)
		rules->must_eat = ft_atol(av[5]);
	else
		rules->must_eat = -1;
	if (rules->philos <= 0 || rules->time_die <= 0 || rules->time_eat <= 0
		|| rules->time_sleep <= 0 || (ac == 6 && rules->must_eat <= 0))
		return (1);
	return (0);	
}
