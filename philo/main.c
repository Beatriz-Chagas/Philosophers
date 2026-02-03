/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchagas <bchagas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 01:50:39 by bchagas           #+#    #+#             */
/*   Updated: 2026/02/03 07:30:27 by bchagas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_forks(t_rules *r)
{
	int	i;

	if(!r->forks)
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
// int main (int ac, char **av)
// {
// 	t_rules	rules;
	
// 	if (parse_args(ac, av, &rules))
// 	{
// 		printf("Invalid arguments.\n");
// 		return (1);
// 	}
// 	else 

// 	return (0);
// }
int	main(int ac, char **av)
{
	t_rules	rules;
	t_philo	*philos;
	int		i;
	pthread_t	mon;

	if (parse_args(ac, av, &rules))
	{
		printf("Invalid arguments.\n");
		return (1);
	}

	// Inicializar mutexes
	rules.dead = 0;
	rules.start_time = get_time();
	pthread_mutex_init(&rules.print, NULL);
	pthread_mutex_init(&rules.death, NULL);

	rules.forks = malloc(sizeof(pthread_mutex_t) * rules.philos);
	i = 0;
	while (i < rules.philos)
	{
		pthread_mutex_init(&rules.forks[i], NULL);
		i++;
	}

	// Inicializar filósofos
	philos = malloc(sizeof(t_philo) * rules.philos);
	i = 0;
	while (i < rules.philos)
	{
		philos[i].id = i + 1;
		philos[i].left_fork = &rules.forks[i];
		philos[i].right_fork = &rules.forks[(i + 1) % rules.philos];
		philos[i].rules = &rules;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = get_time();
		pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]);
		i++;
	}

	// Criar monitor
	pthread_create(&mon, NULL, monitor, philos);

	// Esperar threads terminarem
	i = 0;
	while (i < rules.philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_join(mon, NULL);

	// Destruir mutexes e liberar memória
	i = 0;
	while (i < rules.philos)
	{
		pthread_mutex_destroy(&rules.forks[i]);
		i++;
	}
	pthread_mutex_destroy(&rules.print);
	pthread_mutex_destroy(&rules.death);
	free(rules.forks);
	free(philos);

	return (0);
}
