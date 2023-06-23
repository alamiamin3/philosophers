/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:31:11 by aalami            #+#    #+#             */
/*   Updated: 2023/06/23 10:26:43 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_new_philo(int index, char **argv, long int sim_start)
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
	philo->finished = 0;
	philo->starvation = philo->sim_start + philo->time_to_die;
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

t_list	*creat_philo_list(void)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (0);
	lst->top = NULL;
	return (lst);
}

void	add_philo_to_list(t_list *list, t_philo *philo, int i, int philo_nbr)
{
	t_philo	*tmp;

	if (!philo)
		return ;
	if (list->top == NULL)
		list->top = philo;
	else
	{
		tmp = last_philo(list);
		tmp->next = philo;
	}
	if (i == philo_nbr && philo_nbr != 1)
		philo->next = list->top;
	else
		philo->next = 0;
}

int	add_philosophers(t_list *list, char **argv, long int sim_start)
{
	int		philo_number;
	int		i;
	t_philo	*tmp;

	philo_number = ft_atoi(argv[1]);
	i = 1;
	tmp = NULL;
	while (i <= philo_number)
	{
		tmp = ft_new_philo(i, argv, sim_start);
		if (!tmp)
			return (0);
		add_philo_to_list(list, tmp, i, philo_number);
		i++;
	}
	return (1);
}
