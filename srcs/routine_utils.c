/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:34:31 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/29 16:37:05 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	end_program(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
		pthread_join(table->philo[i++].thread, NULL);
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->philo[i].lfork);
		pthread_mutex_destroy(&table->philo[i].rfork);
		pthread_mutex_destroy(&table->status[i]);
		i++;
	}
}

int	check_status(int i, int ate, t_table *table)
{
	while (i < table->nb_philo)
	{
		pthread_mutex_lock(&table->philo[i].is_eating);
		if (get_timenow() - table->philo[i].last_eat
			> table->time[DIE])
		{
			putstatus(i, "has died");
			pthread_mutex_unlock(&table->philo[i].is_eating);
			return (1);
		}
		else if (table->philo[i].eat_amount == table->philo[i].amount_eaten)
			ate++;
		if (ate == table->nb_philo)
		{
			pthread_mutex_unlock(&table->philo[i].is_eating);
			return (1);
		}
		pthread_mutex_unlock(&table->philo[i].is_eating);
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
	}
}
