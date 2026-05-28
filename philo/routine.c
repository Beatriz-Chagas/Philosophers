/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chagas <chagas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 06:06:13 by bchagas           #+#    #+#             */
/*   Updated: 2026/05/28 05:13:30 by chagas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_forks(t_philo *p)
{
	if (p->has_left)
	{
		pthread_mutex_unlock(p->left_fork);
		p->has_left = 0;
	}
	if (p->has_right && p->right_fork != p->left_fork)
	{
		pthread_mutex_unlock(p->right_fork);
		p->has_right = 0;
	}
}

void	eat_sleep(t_philo *p)
{
	print_status(p, "is eating");
	pthread_mutex_lock(&p->rules->death);
	p->last_meal = get_time();
	p->meals_eaten++;
	pthread_mutex_unlock(&p->rules->death);
	ft_usleep(p->rules->time_eat, p->rules);
	put_forks(p);
	print_status(p, "is sleeping");
	ft_usleep(p->rules->time_sleep, p->rules);
}

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->id % 2 == 0)
		usleep(1000);
	while (!simulation_finished(p->rules))
	{
		if (!take_forks(p))
			continue ;
		if (simulation_finished(p->rules))
			break ;
		eat_sleep(p);
		if (simulation_finished(p->rules))
			break ;
		print_status(p, "is thinking");
		usleep(500);
	}
	return (NULL);
}
