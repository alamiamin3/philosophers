/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 21:56:02 by aalami            #+#    #+#             */
/*   Updated: 2023/06/23 11:13:39 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		philo_thread;
	int				index;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		number_of_meals;
	long int		sim_start;
	long long		starvation;
	int				nbr_of_philos;
	int				died;
	int				finished;
	pthread_mutex_t	fork;
	pthread_mutex_t	*action;
	struct s_philo	*next;
}					t_philo;

typedef struct s_list
{
	t_philo			*top;
}					t_list;

size_t				ft_strlen(const char *s);
long long			ft_atoi(const char *str);
int					ft_isdigit(int c);
t_philo				*ft_new_philo(int index, char **argv, long int sim_start);
t_philo				*last_philo(t_list *lst);
void				add_philo_to_list(t_list *list, t_philo *philo, int i,
						int philo_nbr);
t_list				*creat_philo_list(void);
int					add_philosophers(t_list *list, char **argv,
						long int sim_start);
void				print_actions(t_philo *tmp, int stat);
int					check_args(int argc, char **argv);
int					check_is_numerique(char *str);
void				ft_usleep(time_t time_stamps);
long long			get_current(void);
void				free_philo_list(t_list *philo_lst);
int					check_philo_meals(t_list *philo_lst);
#endif