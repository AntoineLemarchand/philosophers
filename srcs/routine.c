/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 10:43:22 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/31 10:05:43 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	tryeat(t_philo *philo)
{
	pthread_mutex_lock(&philo->lfork);
	putstatus(philo->id, "has taken a fork");
	pthread_mutex_lock(&philo->rfork);
	putstatus(philo->id, "has taken a fork");
	putstatus(philo->id, "is eating");
	pthread_mutex_lock(&philo->is_eating);
	philo->last_eat = get_timenow();
	usleep(philo->time[EAT] * 1000);
	philo->amount_eaten++;
	pthread_mutex_unlock(&philo->is_eating);
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
	putstatus(philo->id, "is sleeping");
	usleep(philo->time[SLEEP] * 1000);
	putstatus(philo->id, "is thinking");
	return (0);
}

void	only_philo(t_table *table)
{
	printf("%u %i has taken a fork\n", get_timenow(), 0);
	usleep(table->time[DIE] * 1000);
	printf("%u %i has died\n", get_timenow(), 0);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2 == 0)
		usleep(philo->time[EAT] / 10);
	while (1)
		if (routine_helper(philo))
			break ;
	return (NULL);
}
