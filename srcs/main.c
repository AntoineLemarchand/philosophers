/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 09:54:52 by alemarch          #+#    #+#             */
/*   Updated: 2022/01/26 14:58:17 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	get_timenow(void)
{
	struct timeval	curr;

	if (gettimeofday(&curr, NULL) < 0)
		return (0);
	return (curr.tv_sec * 1000 + curr.tv_usec / 1000);
}

t_table	*init_table(int ac, char **av)
{
	t_table *table;

	table = malloc(sizeof(t_table));
	table->timestamp = get_timenow();
	if (!table || ac < 5 || ft_atol(av[1]) <= 0 || ft_atol(av[2]) < 0
		|| ft_atol(av[3]) < 0 || ft_atol(av[4]) < 0)
	{
		free(table);
		return (NULL);
	}
	table->nb_philo = (int)ft_atol(av[1]);
	table->t_die = (unsigned int)ft_atol(av[2]);
	table->t_eat = (unsigned int)ft_atol(av[3]);
	table->t_sleep = (unsigned int)ft_atol(av[4]);
	if (av[5] && (unsigned int)ft_atol(av[5]) < 0)
	{
		free(table);
		return (NULL);
	}
	else if (av[5])
		table->eat_amount = (int)ft_atol(av[5]);
	else
		table->eat_amount = 0;
	return (table);
}

static void	init_philo(t_philo philo, int i)
{
	philo.id = i;
	philo.amount_eaten = 0;
	philo.last_eat = -1;
	philo.last_action = -1;
}

int	sit_philo(t_table *table)
{
	int	i;

	i = 0;
	if (pthread_create(&table->philo[i].thread, NULL, (void *)printf, "coucou") != 0)
		return (1);
	table->philo[i].lfork = table->forks[table->nb_philo - 1];
	table->philo[i].rfork = table->forks[i + 1];
	i++;
	while (i < table->nb_philo - 1)
	{
		if (pthread_create(&table->philo[i].thread, NULL, (void *)printf, "coucou") != 0)
			return (1);
		init_philo(table->philo[i], i);
		table->philo[i].lfork = table->forks[i - 1];
		table->philo[i].rfork = table->forks[i + 1];
		i++;
	}
	if (pthread_create(&table->philo[i].thread, NULL, (void *)printf, "coucou") != 0)
		return (1);
	table->philo[i].lfork = table->forks[i - 1];
	table->philo[i].rfork = table->forks[0];
	return (0);
}

int	set_table(t_table *table)
{
	int	i;

	i = 0;
	table->philo = malloc(table->nb_philo * sizeof(pthread_t));
	if (!table->philo)
		return (1);
	table->forks = malloc(table->nb_philo * sizeof(pthread_mutex_t));
	if (!table->forks)
	{
		free(table->philo);
		return (1);
	}
	while (i < table->nb_philo)
		pthread_mutex_init(&table->forks[i++], NULL);
	if (sit_philo(table))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_table *table;

	table = init_table(ac, av);
	if (!table || set_table(table))
	{
		write(2, "Argument error\n", 15);
		return (22);
	}
	printf("nb_philo: %u\n", table->nb_philo);
	printf("t_die: %u\n", table->t_die);
	printf("t_eat: %u\n", table->t_eat);
	printf("t_sleep: %u\n", table->t_sleep);
	printf("eat_amount: %u\n", table->eat_amount);
	printf("timestamp: %li\n", table->timestamp);
	free(table);
	return (0);
}
