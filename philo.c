/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 21:55:22 by aalami            #+#    #+#             */
/*   Updated: 2023/06/10 18:33:50 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_is_numerique(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;	
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	int	i = 1;
	if (argc != 5 && argc != 6)
		return (0);
	while(argv[i])
	{
		if (ft_atoi(argv[i]) < 0 || !check_is_numerique(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

t_list	*creat_philo_list()
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
	if (i == philo_nbr)
		philo->next = list->top;
	else
		philo->next = 0;
}

int	add_philosophers(t_list *list, char **argv)
{
	int	philo_number;
	int	i;
	t_philo	*tmp;
	
	philo_number = ft_atoi(argv[1]);
	i = 1;
	tmp = NULL;
	while (i <= philo_number)
	{
		tmp = ft_new_philo(i, argv);
		if (!tmp)
			return (0);
		add_philo_to_list(list, tmp, i, philo_number);
		i++;
	}
	return (1);
}
void	routine(t_philo *tmp)
{
	while (1)
	{
		if (pthread_mutex_lock(&tmp->fork) != -1 && pthread_mutex_lock(&tmp->next->fork) != -1)
		{
			printf("philo %d take a fork\n", tmp->index);	
			printf("philo %d take a fork\n", tmp->index);
			printf("philo %d is eating\n", tmp->index);
			usleep(tmp->time_to_eat);
			pthread_mutex_unlock(&tmp->fork);
			pthread_mutex_unlock(&tmp->next->fork);
			printf("philo %d is sleeping\n", tmp->index);
			usleep(tmp->time_to_sleep);
		}
		else
		{
			printf("philo %d is thinking\n", tmp->index);
			usleep(tmp->time_to_die);
			printf("philo %d died\n", tmp->index);
			exit (0);
		}
			
	}
}
int	init_philos(t_list *philo_lst)
{
	t_philo	*tmp;

	tmp = philo_lst->top;
	while (tmp)
	{
		pthread_mutex_init(&tmp->fork, NULL);
		pthread_create(&tmp->philo_thread, NULL, (void *)&routine, (void *)tmp);
		tmp = tmp->next;
		if (tmp == philo_lst->top)
			break;
	}
	return (0);
}
int	wait_for_philos(t_list *philo_lst)
{
	t_philo	*tmp;

	tmp = philo_lst->top;
	while(tmp)
	{
		pthread_join(tmp->philo_thread, NULL);
		tmp = tmp->next;
		if (tmp == philo_lst->top)
			break;
	}
	return (0);
}
int	main(int argc, char **argv)
{
	t_list	*philo_lst;
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
		if (!add_philosophers(philo_lst, argv))
			return (1);
		init_philos(philo_lst);
		wait_for_philos(philo_lst);
	}
	// t_philo *tmp = philo_lst->top;
	// // int i = 1;
	// while (tmp)
	// {
	// 	printf("philo number %d \n", tmp->index);
	// 	tmp = tmp->next;
	// }
	return (0);
}