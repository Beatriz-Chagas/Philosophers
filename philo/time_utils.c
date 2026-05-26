/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chagas <chagas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 06:46:31 by bchagas           #+#    #+#             */
/*   Updated: 2026/05/26 03:29:09 by chagas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	ft_usleep(long time, t_rules *r)
{
	long	start;

	start = get_time();
	while (!simulation_finished(r))
	{
		if (get_time() - start >= time)
			break ;
		usleep(500);
	}
}

void	print_status(t_philo *p, char *msg)
{
	pthread_mutex_lock(&p->rules->print);
	pthread_mutex_lock(&p->rules->death);
	if (!p->rules->dead || !ft_strcmp(msg, "died"))
	{
		printf("%ld %d %s\n",
			get_time() - p->rules->start_time,
			p->id,
			msg);
	}
	pthread_mutex_unlock(&p->rules->death);
	pthread_mutex_unlock(&p->rules->print);
}
