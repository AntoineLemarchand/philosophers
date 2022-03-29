/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 10:00:37 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/29 11:17:58 by alemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define DIE 0
# define EAT 1
# define SLEEP 2

typedef struct s_philo 
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	lfork;
	pthread_mutex_t	rfork;
	unsigned int	time[3];
	int				eat_amount;
	int				amount_eaten;
	long			timestamp;
	int				dead;
} t_philo;

typedef struct s_table
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	int				nb_philo;
	unsigned int	time[3];
	int				eat_amount;
	long			timestamp;
} t_table;

// utils.c
long	ft_atol(const char *nptr);
// routine.c
void	putstatus(int i, char *s);
void	*routine(void *data);
// main.c
unsigned int	get_timenow(void);
#endif
