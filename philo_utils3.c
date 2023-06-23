/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 10:37:51 by aalami            #+#    #+#             */
/*   Updated: 2023/06/23 10:48:13 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philo_list(t_list *philo_lst)
{
	t_philo	*philo;

	philo = philo_lst->top;
	while (philo)
	{
		free(philo);
		philo = philo->next;
		if (philo == philo_lst->top)
			break ;
	}
	free(philo_lst);
}

int	check_philo_meals(t_list *philo_lst)
{
	t_philo	*tmp;
	int		finished_meals;

	tmp = philo_lst->top;
	finished_meals = 0;
	while (tmp)
	{
		if (tmp->finished == 1)
			finished_meals++;
		tmp = tmp->next;
		if (tmp == philo_lst->top)
			break ;
	}
	if (finished_meals == philo_lst->top->nbr_of_philos)
		return (1);
	return (0);
}
