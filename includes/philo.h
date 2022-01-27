/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 10:00:37 by alemarch          #+#    #+#             */
/*   Updated: 2022/01/27 22:03:28 by alemarch         ###   ########.fr       */
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
	int				id;
	pthread_t		thread;
	pthread_mutex_t	lfork;
	pthread_mutex_t	rfork;
	unsigned int	t_die;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	int				eat_amount;
} t_philo;

typedef struct s_table
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	int				nb_philo;
	unsigned int	t_die;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	int				eat_amount;
	long			timestamp;
} t_table;
// utils.c
long	ft_atol(const char *nptr);
// routine.c
void	*routine(void *data);
// main.c
unsigned int	get_timenow(void);
#endif
