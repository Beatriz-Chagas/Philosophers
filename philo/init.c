/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchagas <bchagas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 23:51:02 by bchagas           #+#    #+#             */
/*   Updated: 2026/02/03 07:25:41 by bchagas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_rules *r)
{
	int	i;

	r->forks = malloc(sizeof(pthread_mutex_t) * r->philos);
	if (!r->forks)
		return (1);
	i = 0;
	while (i < r->philos)
	{
		pthread_mutex_init(&r->forks[i], NULL);
		i++;
	}
	return (0);
}


int	init_philos(t_rules *r, t_philo **philos)
{
	int	i;
	
	*philos = malloc(sizeof(t_philo) * r->philos);
	if (!*philos)
	return (1);
	i = 0;
	while (i < r->philos)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].meals_eaten = 0;
		(*philos)[i].last_meal = r->start_time;
		(*philos)[i].left_fork = &r->forks[i];
		(*philos)[i].right_fork = &r->forks[(i + 1) % r->philos];
		(*philos)[i].rules = r;
		i++;
	}
	return (0);
}
// int	init_rules(t_rules *r)
// {
// 	r->dead = 0;
// 	r->start_time = get_time();
// 	pthread_mutex_init(&r->print, NULL);
// 	pthread_mutex_init(&r->death, NULL);
// 	return (0);
// }
