/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:34:31 by alemarch          #+#    #+#             */
/*   Updated: 2022/04/05 16:27:55 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	end_program(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_lock(&table->status[i]);
		table->philo[i].dead = 1;
		pthread_mutex_unlock(&table->status[i]);
		i++;
	}
	i = 0;
	while (table->nb_philo != 1 && i < table->nb_philo)
		pthread_join(table->philo[i++].thread, NULL);
	pthread_mutex_destroy(&table->print);
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->status[i]);
		i++;
	}
}

int	check_status(int i, int ate, t_table *table)
{
	while (i < table->nb_philo)
	{
		pthread_mutex_lock(&table->status[i]);
		if (get_timenow() - table->philo[i].last_eat
			> table->time[DIE])
		{
			pthread_mutex_unlock(&table->status[i]);
			putstatus(&table->philo[i], "has died");
			return (1);
		}
		if (table->eat_amount == table->philo[i].amount_eaten)
			ate++;
		if (ate == table->nb_philo)
		{
			pthread_mutex_unlock(&table->status[i]);
			return (1);
		}
		pthread_mutex_unlock(&table->status[i]);
		i++;
	}
	return (0);
}

void	end_check(t_table *table)
{
	while (1)
	{
		if (check_status(0, 0, table))
			break ;
		else
			usleep(100);
	}
}
