/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchagas- <bchagas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 01:50:39 by bchagas           #+#    #+#             */
/*   Updated: 2026/05/26 21:03:48 by bchagas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_forks(t_rules *r)
{
	int	i;

	if (!r->forks)
		return ;
	i = 0;
	while (i < r->philos)
	{
		pthread_mutex_destroy(&r->forks[i]);
		i++;
	}
	free(r->forks);
	r->forks = NULL;
}

static int	init_rules(t_rules *rules)
{
	int	i;

	rules->dead = 0;
	rules->start_time = get_time();
	pthread_mutex_init(&rules->print, NULL);
	pthread_mutex_init(&rules->death, NULL);
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->philos);
	if (!rules->forks)
		return (1);
	i = 0;
	while (i < rules->philos)
	{
		pthread_mutex_init(&rules->forks[i], NULL);
		i++;
	}
	return (0);
}

static t_philo	*init_philos(t_rules *rules)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * rules->philos);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < rules->philos)
	{
		philos[i].id = i + 1;
		philos[i].left_fork = &rules->forks[i];
		philos[i].right_fork = &rules->forks[(i + 1) % rules->philos];
		philos[i].rules = rules;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = get_time();
		pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]);
		i++;
	}
	return (philos);
}

static void	cleanup(t_rules *rules, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < rules->philos)
		pthread_join(philos[i++].thread, NULL);
	destroy_forks(rules);
	pthread_mutex_destroy(&rules->print);
	pthread_mutex_destroy(&rules->death);
	free(philos);
}

int	main(int ac, char **av)
{
	t_rules		rules;
	t_philo		*philos;
	pthread_t	monitor;

	if (parse_args(ac, av, &rules))
		return (printf("Invalid arguments.\n"), 1);
	if (init_rules(&rules))
		return (1);
	philos = init_philos(&rules);
	if (!philos)
		return (1);
	pthread_create(&monitor, NULL, monitor_routine, philos);
	pthread_join(monitor, NULL);
	cleanup(&rules, philos);
	return (0);
}
