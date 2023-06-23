/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 21:55:22 by aalami            #+#    #+#             */
/*   Updated: 2023/06/23 12:25:45 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(t_philo *tmp)
{
	if (tmp->index % 2 == 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&tmp->fork);
		print_actions(tmp, 1);
		if (tmp->next)
			pthread_mutex_lock(&tmp->next->fork);
		else
		{
			pthread_mutex_lock(tmp->action);
			tmp->starvation = get_current() + tmp->time_to_die;
			pthread_mutex_unlock(tmp->action);
			return ;
		}
		print_actions(tmp, 1);
		print_actions(tmp, 2);
		ft_usleep(tmp->time_to_eat);
		pthread_mutex_unlock(&tmp->fork);
		pthread_mutex_unlock(&tmp->next->fork);
		print_actions(tmp, 3);
		ft_usleep(tmp->time_to_sleep);
		print_actions(tmp, 4);
	}
}

int	stop_simulation(t_list *philo_lst)
{
	t_philo	*tmp;

	tmp = philo_lst->top;
	pthread_mutex_lock(tmp->action);
	while (tmp)
	{
		if (get_current() - tmp->starvation == 0)
		{
			printf("%lld philo %d died\n", tmp->starvation - tmp->sim_start,
				tmp->index);
			return (1);
		}
		if (check_philo_meals(philo_lst))
		{
			pthread_mutex_unlock(tmp->action);
			return (1);
		}
		tmp = tmp->next;
		if (tmp == philo_lst->top)
			break ;
	}
	pthread_mutex_unlock(philo_lst->top->action);
	return (0);
}

int	creat_threads(t_list *philo_lst, pthread_mutex_t check)
{
	t_philo	*tmp;

	tmp = philo_lst->top;
	while (tmp)
	{
		if (pthread_mutex_init(&tmp->fork, NULL) != 0)
			return (1);
		tmp->action = &check;
		pthread_create(&tmp->philo_thread, NULL, (void *)&routine, (void *)tmp);
		pthread_detach(tmp->philo_thread);
		tmp = tmp->next;
		if (tmp == philo_lst->top)
			break ;
	}
	return (0);
}

int	init_philos(t_list *philo_lst)
{
	pthread_mutex_t	check;

	if (pthread_mutex_init(&check, NULL) != 0)
		return (1);
	if (creat_threads(philo_lst, check))
		return (1);
	while (1)
	{
		if (stop_simulation(philo_lst))
			break ;
		usleep(50);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	long long	sim_start;
	t_list		*philo_lst;

	if (!check_args(argc, argv))
	{
		printf("Error\n");
		return (1);
	}
	else
	{
		philo_lst = creat_philo_list();
		if (!philo_lst)
			return (1);
		sim_start = get_current();
		if (!add_philosophers(philo_lst, argv, sim_start))
			return (1);
		if (init_philos(philo_lst) == 1)
			return (1);
		free_philo_list(philo_lst);
	}
	return (0);
}
