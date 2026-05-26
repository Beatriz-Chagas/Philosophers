/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chagas <chagas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 06:53:09 by bchagas           #+#    #+#             */
/*   Updated: 2026/05/26 04:38:36 by chagas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_philo *p, int i, long last)
{
	pthread_mutex_lock(&p[0].rules->death);
	if (!p[0].rules->dead)
	{
		p[0].rules->dead = 1;
		pthread_mutex_unlock(&p[0].rules->death);
		pthread_mutex_lock(&p[0].rules->print);
		printf("%ld %d died\n",
			get_time() - p[0].rules->start_time,
			p[i].id);
		pthread_mutex_unlock(&p[0].rules->print);
		return (1);
	}
	pthread_mutex_unlock(&p[0].rules->death);
	(void)last;
	return (0);
}

static int	check_philo(t_philo *p, int i, int *finished)
{
	long	last;

	pthread_mutex_lock(&p[0].rules->death);
	last = p[i].last_meal;
	if (p[0].rules->must_eat > 0
		&& p[i].meals_eaten >= p[0].rules->must_eat)
		(*finished)++;
	pthread_mutex_unlock(&p[0].rules->death);
	if (get_time() - last >= p[0].rules->time_die)
		return (check_death(p, i, last));
	return (0);
}

static int	all_finished(t_philo *p, int finished)
{
	if (p[0].rules->must_eat > 0
		&& finished >= p[0].rules->philos)
	{
		pthread_mutex_lock(&p[0].rules->death);
		p[0].rules->dead = 1;
		pthread_mutex_unlock(&p[0].rules->death);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo	*p;
	int		i;
	int		finished;

	p = (t_philo *)arg;
	while (!simulation_finished(p[0].rules))
	{
		i = 0;
		finished = 0;
		while (i < p[0].rules->philos)
		{
			if (check_philo(p, i, &finished))
				return (NULL);
			i++;
		}
		if (all_finished(p, finished))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

int	simulation_finished(t_rules *rules)
{
	int	dead;

	pthread_mutex_lock(&rules->death);
	dead = rules->dead;
	pthread_mutex_unlock(&rules->death);
	return (dead);
}
