/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarch <alemarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 10:00:37 by alemarch          #+#    #+#             */
/*   Updated: 2022/03/29 15:01:30 by alemarch         ###   ########.fr       */
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

# define DEAD 1
# define FULL 2

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
	pthread_mutex_t	status_mutex;
	int				status;
}	t_philo;

typedef struct s_table
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*status;
	int				nb_philo;
	unsigned int	time[3];
	int				eat_amount;
	long			timestamp;
}	t_table;

// utils.c
long			ft_atol(const char *nptr);
unsigned int	get_timenow(void);
// routine_utils.c
void			end_check(t_table *table);
// routine.c
void			putstatus(int i, char *s);
void			*routine(void *data);
#endif
