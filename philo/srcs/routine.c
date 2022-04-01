/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 10:43:22 by alemarch          #+#    #+#             */
/*   Updated: 2022/04/01 09:34:47 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_usleep(unsigned time)
{
	unsigned	now;

	now = get_timenow();
	while (get_timenow() - now < time)
		usleep(10);
}

static void	tryeat(t_philo *philo)
{
	pthread_mutex_lock(&philo->lfork);
	putstatus(philo->id, philo->timestamp, "has taken a fork");
	pthread_mutex_lock(&philo->rfork);
	putstatus(philo->id, philo->timestamp, "has taken a fork");
	pthread_mutex_lock(&philo->is_eating);
	putstatus(philo->id, philo->timestamp, "is eating");
	philo->last_eat = get_timenow();
	pthread_mutex_unlock(&philo->is_eating);
	philo->amount_eaten++;
	ft_usleep(philo->time[EAT]);
	pthread_mutex_unlock(&philo->rfork);
	pthread_mutex_unlock(&philo->lfork);
}

static int	routine_helper(t_philo *philo)
{
	if (get_timenow() - philo->last_eat >= philo->time[DIE])
		return (1);
	else if (philo->amount_eaten
		&& philo->amount_eaten == philo->eat_amount)
		return (1);
	tryeat(philo);
	putstatus(philo->id, philo->timestamp, "is sleeping");
	ft_usleep(philo->time[SLEEP]);
	putstatus(philo->id, philo->timestamp, "is thinking");
	return (0);
}

void	only_philo(t_table *table)
{
	putstatus(0, table->timestamp, "has taken a fork");
	ft_usleep(table->time[DIE]);
	putstatus(0, table->timestamp, "has died");
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2 == 0)
		ft_usleep(philo->time[EAT] / 2);
	while (1)
		if (routine_helper(philo))
			break ;
	return (NULL);
}
