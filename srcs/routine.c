/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 10:43:22 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/29 14:01:47 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	putstatus(int i, char *s)
{
	printf("%u %i %s\n", get_timenow(), i, s);
}

void	tryeat(t_philo *philo, int amount_eaten, long t_without_eating,
		long last_eat)
{
	pthread_mutex_lock(&philo->lfork);
	putstatus(philo->id, "has taken a fork");
	pthread_mutex_lock(&philo->rfork);
	putstatus(philo->id, "has taken a fork");
	putstatus(philo->id, "is eating");
	usleep(philo->time[EAT] * 1000);
	pthread_mutex_unlock(&philo->rfork);
	pthread_mutex_unlock(&philo->lfork);
	amount_eaten++;
	t_without_eating = 0;
	last_eat = get_timenow();
}

void	*routine(void *args)
{
	t_philo	*philo;
	int		amount_eaten;
	long	t_without_eating;
	long	last_eat;
	int		status;

	status = 0;
	philo = (t_philo *)args;
	amount_eaten = 0;
	t_without_eating = 0;
	last_eat = philo->timestamp;
	if (philo->id % 2 == 0)
		usleep(philo->time[EAT] * 1000);
	while (!status)
	{	
		pthread_mutex_lock(&philo->status_mutex);
		if (t_without_eating >= philo->time[DIE])
		{
			philo->status = DEAD;
			pthread_mutex_unlock(&philo->status_mutex);
			status = DEAD;
			return (NULL);
		}
		else if (philo->amount_eaten
			&& philo->amount_eaten == philo->eat_amount)
		{
			philo->status = FULL;
			pthread_mutex_unlock(&philo->status_mutex);
			status = FULL;
			return (NULL);
		}
		pthread_mutex_unlock(&philo->status_mutex);
		t_without_eating = get_timenow() - last_eat;
		tryeat(philo, amount_eaten, t_without_eating, last_eat);
		putstatus(philo->id, "is sleeping");
		usleep(philo->time[SLEEP] * 1000);
		putstatus(philo->id, "is thinking");
	}
	return (NULL);
}
