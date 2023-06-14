/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:31:11 by aalami            #+#    #+#             */
/*   Updated: 2023/06/14 17:00:47 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*	ft_new_philo(int index, char **argv, long int sim_start)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!(philo))
		return (0);
	philo->index = index;
	philo->nbr_of_philos = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->number_of_meals = ft_atoi(argv[5]);
	else
		philo->number_of_meals = -1;
	philo->sim_start = sim_start;
	philo->next = NULL;
	return (philo);
}

t_philo	*last_philo(t_list *lst)
{
	t_philo	*tmp;

	if (lst->top == NULL)
		return (0);
	tmp = lst->top;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}
