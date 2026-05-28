/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chagas <chagas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 05:14:09 by chagas            #+#    #+#             */
/*   Updated: 2026/05/28 05:15:36 by chagas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lock_fork(t_philo *p, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	if (fork == p->left_fork)
		p->has_left = 1;
	else
		p->has_right = 1;
	print_status(p, "has taken a fork");
}

static int	one_philo(t_philo *p, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	p->has_left = 1;
	print_status(p, "has taken a fork");
	ft_usleep(p->rules->time_die, p->rules);
	put_forks(p);
	return (0);
}

int	take_forks(t_philo *p)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	p->has_left = 0;
	p->has_right = 0;
	if (simulation_finished(p->rules))
		return (0);
	first = p->left_fork;
	second = p->right_fork;
	if (first == second)
		return (one_philo(p, first));
	if (first > second)
	{
		first = p->right_fork;
		second = p->left_fork;
	}
	lock_fork(p, first);
	if (simulation_finished(p->rules))
		return (put_forks(p), 0);
	lock_fork(p, second);
	if (simulation_finished(p->rules))
		return (put_forks(p), 0);
	return (1);
}
