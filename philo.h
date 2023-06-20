/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 21:56:02 by aalami            #+#    #+#             */
/*   Updated: 2023/06/20 04:26:26 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		philo_thread;
	int				index;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		number_of_meals;
	long int		sim_start;
	int				nbr_of_philos;
	int				*died;
	pthread_mutex_t fork;
	pthread_mutex_t death;
	struct s_philo	*next;
}					t_philo;

typedef struct s_list
{
	t_philo			*top;
}					t_list;

size_t				ft_strlen(const char *s);
long long			ft_atoi(const char *str);
int					ft_isdigit(int c);
t_philo             *ft_new_philo(int index, char **argv, long int sim_start);
t_philo	            *last_philo(t_list *lst);
#endif