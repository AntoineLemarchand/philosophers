/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 10:43:22 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/29 15:29:45 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	putstatus(int i, char *s)
{
	printf("%u %i %s\n", get_timenow(), i, s);
}

int	tryeat(t_philo *philo, long last_eat)
{
	pthread_mutex_lock(&philo->lfork);
	putstatus(philo->id, "has taken a fork");
	pthread_mutex_lock(&philo->rfork);
	putstatus(philo->id, "has taken a fork");
	putstatus(philo->id, "is eating");
	usleep(philo->time[EAT] * 1000);
	pthread_mutex_unlock(&philo->rfork);
	pthread_mutex_unlock(&philo->lfork);
	if (get_timenow() - last_eat < philo->time[DIE])
		last_eat = get_timenow();
	return (last_eat);
}

int	routine_helper(t_philo *philo, unsigned int last_eat)
{
	pthread_mutex_lock(&philo->status_mutex);
	if (get_timenow() - last_eat >= philo->time[DIE])
	{
		philo->status = DEAD;
		pthread_mutex_unlock(&philo->status_mutex);
		return (1);
	}
	else if (philo->amount_eaten
		&& philo->amount_eaten == philo->eat_amount)
	{
		philo->status = FULL;
		pthread_mutex_unlock(&philo->status_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->status_mutex);
	last_eat = tryeat(philo, last_eat);
	philo->amount_eaten++;
	putstatus(philo->id, "is sleeping");
	usleep(philo->time[SLEEP] * 1000);
	putstatus(philo->id, "is thinking");
	return (0);
}

void	*routine(void *args)
{
	t_philo	*philo;
	long	last_eat;

	philo = (t_philo *)args;
	last_eat = philo->timestamp;
	if (philo->id % 2 == 0)
		usleep(philo->time[EAT] / 10);
	while (1)
		if(routine_helper(philo, last_eat))
			break;
	return (NULL);
}
