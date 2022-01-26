/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 10:00:37 by alemarch          #+#    #+#             */
/*   Updated: 2022/01/26 11:19:04 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo 
{
	int	id;
} t_philo;

typedef struct t_fork
{
	int	id;
} t_fork;

typedef struct s_table
{
	t_philo			philos[200];
	t_fork			forks[200];
	unsigned int	nb_philo;
	unsigned int	t_die;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	unsigned int	eat_amount;
} t_table;
#endif
