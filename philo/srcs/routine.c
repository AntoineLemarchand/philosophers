/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 10:43:22 by alemarch          #+#    #+#             */
/*   Updated: 2022/04/05 16:35:59 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_usleep(unsigned int time)
{
	unsigned int	now;

	now = get_timenow();
	while (get_timenow() - now < time)
		usleep(100);
}

static void	tryeat(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	putstatus(philo, "has taken a fork");
	pthread_mutex_lock(philo->rfork);
	putstatus(philo, "has taken a fork");
	putstatus(philo, "is eating");
	pthread_mutex_lock(philo->status);
	philo->last_eat = get_timenow();
	philo->amount_eaten++;
	pthread_mutex_unlock(philo->status);
	ft_usleep(philo->time[EAT]);
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(philo->lfork);
	putstatus(philo, "is sleeping");
	ft_usleep(philo->time[SLEEP]);
}

static int	routine_helper(t_philo *philo)
{
	pthread_mutex_lock(philo->status);
	if (philo->dead)
	{
		pthread_mutex_unlock(philo->status);
		return (1);
	}
	pthread_mutex_unlock(philo->status);
	tryeat(philo);
	putstatus(philo, "is thinking");
	return (0);
}

void	only_philo(t_table *table)
{
	putstatus(table->philo, "has taken a fork");
	ft_usleep(table->time[DIE]);
	putstatus(table->philo, "has died");
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2 == 0)
		ft_usleep(philo->time[EAT]);
	while (1)
		if (routine_helper(philo))
			break ;
	return (NULL);
}
