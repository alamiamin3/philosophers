/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 21:55:22 by aalami            #+#    #+#             */
/*   Updated: 2023/06/22 05:54:43 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	long get_current()
{
	struct	timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 ) + (tv.tv_usec / 1000);
}


void    usleep__(time_t time_stamps)
{
    long long current = get_current();
    while (get_current()  - current < time_stamps)
  	{
		usleep(50);
	}
    
}

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
		if (ft_atoi(argv[i]) <= 0 || !check_is_numerique(argv[i]))
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
	if (i == philo_nbr && philo_nbr != 1)
		philo->next = list->top;
	else
		philo->next = 0;
}

int	add_philosophers(t_list *list, char **argv, long int sim_start)
{
	int	philo_number;
	int	i;
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
void	destroy_all_forks(t_philo *tmp)
{
	int i;
	t_philo	*philo;

	philo = tmp;
	i = 1;
		pthread_mutex_destroy(philo->action);
		pthread_mutex_destroy(philo->death);
	while (i <= philo->nbr_of_philos)
	{
			// pthread_mutex_unlock(&philo->fork);
			// // pthread_mutex_lock(&philo->fork);
		pthread_mutex_destroy(&philo->fork);
		i++;
		philo = philo->next;
	}
}
// int	stop_simulation(t_philo *philo)
// {
// 	int	i;
// 	t_philo	*tmp;

// 	tmp = philo;
// 	i = 1;
// 	while(i <= tmp->nbr_of_philos)
// 	{
// 		if (tmp->died == 1)
// 			return (1);
// 		i++;
// 		tmp = tmp->next;
// 	}

// 	return (0);
// }
void	lock_for_death(t_philo *philo)
{
	int	i;
	t_philo	*tmp;

	tmp = philo;
	i = 1;
	// tmp->died = 1;
	while (i <= tmp->nbr_of_philos)
	{
		pthread_mutex_lock(tmp->death);
		tmp = tmp->next;
		i++;
	}
}
void	unlock_for_death(t_philo *philo)
{
	int	i;
	t_philo	*tmp;

	tmp = philo;
	i = 1;
	while (i <= tmp->nbr_of_philos)
	{
		pthread_mutex_unlock(tmp->death);
		tmp = tmp->next;
		i++;
	}
}
int	detach_all_philos(t_philo *philo)
{
	t_philo	*tmp;
	int i;

	i = 1;
	tmp = philo->next;
	while(i < tmp->nbr_of_philos)
	{
		pthread_detach(tmp->philo_thread);
		tmp = tmp->next;
		i++;
	}
	return (0);
}
void	routine(t_philo *tmp)
{
	// struct	timeval tv;
	// pthread_mutex_t	death;
	// printf("Start %lld\n",);
	if(tmp->index % 2 == 0)
		usleep(50);
	while (1)
	{
		// if (pthread_mutex_lock(&tmp->fork) != -1 && pthread_mutex_lock(&tmp->next->fork) != -1)
		// {
			pthread_mutex_lock(tmp->action);
			if (pthread_mutex_lock(&tmp->fork) != -1)
			printf("%lld philo %d take a fork\n", get_current() - tmp->sim_start, tmp->index);
			pthread_mutex_unlock(tmp->action);
			if (pthread_mutex_lock(&tmp->next->fork) != -1)
			pthread_mutex_lock(tmp->action);
			printf("%lld philo %d take a fork\n", get_current() - tmp->sim_start, tmp->index);
			pthread_mutex_unlock(tmp->action);
			pthread_mutex_lock(tmp->action);
			printf("%lld philo %d is eating\n", get_current() - tmp->sim_start, tmp->index);
			tmp->starvation = get_current() + tmp->time_to_die;
			if (tmp->number_of_meals != -1)
			{
				tmp->number_of_meals --;
				if (tmp->number_of_meals == 0)
					tmp->finished = 1;	
			}
			pthread_mutex_unlock(tmp->action);
			usleep__(tmp->time_to_eat);
			pthread_mutex_unlock(&tmp->fork);
			pthread_mutex_unlock(&tmp->next->fork);
			pthread_mutex_lock(tmp->action);
			printf("%lld philo %d is sleeping\n", get_current() - tmp->sim_start, tmp->index);
			pthread_mutex_unlock(tmp->action);
			usleep__(tmp->time_to_sleep);
			pthread_mutex_lock(tmp->action);
				// pthread_mutex_lock(&tmp->death);
			printf("%lld philo %d is thinking\n", get_current() - tmp->sim_start, tmp->index);
			pthread_mutex_unlock(tmp->action);

	}
	// pthread_mutex_unlock(tmp->death);
	
}

int	check_philo_meals(t_list *philo_lst)
{
	t_philo	*tmp;
	int	finished_meals;

	tmp = philo_lst->top;
	finished_meals = 0;
	while (tmp)
	{
		if (tmp->finished == 1)
			finished_meals ++;
		tmp = tmp->next;
		if (tmp == philo_lst->top)
			break;
	}
	// printf("%d---\n",finished_meals);
	if (finished_meals == tmp->nbr_of_philos)
		return (1);
	return (0);
}
int	check_death(t_list *philo_lst)
{
	t_philo	*tmp;
	// pthread_mutex_t death;
	
	// pthread_mutex_init(&death, NULL);
	tmp = philo_lst->top;
	pthread_mutex_lock(tmp->action);
	while (tmp)
	{
		if (get_current() - tmp->starvation == 0)
		{
			
			printf("%lld philo %d died\n", tmp->starvation - tmp->sim_start, tmp->index);
			// pthread_mutex_unlock(tmp->action);
			return (1);
		}
		if (check_philo_meals(philo_lst))
		{
			pthread_mutex_unlock(tmp->action);
			return (1);
		}
		tmp = tmp->next;
		if (tmp == philo_lst->top)
			break;
	}
	pthread_mutex_unlock(tmp->action);
	return (0);
}
int	wait_for_philos(t_list *philo_lst)
{
	t_philo	*tmp;
	int i;

	i = 1;
	tmp = philo_lst->top;
	while(i <= tmp->nbr_of_philos)
	{
		pthread_join(tmp->philo_thread, NULL);
		tmp = tmp->next;
		i++;
	}
	return (0);
}
int	init_philos(t_list *philo_lst)
{
	t_philo	*tmp;
	pthread_mutex_t death;
	pthread_mutex_t check;
	long long	check_time;
	pthread_mutex_init(&check, NULL);
	pthread_mutex_init(&death, NULL);
	tmp = philo_lst->top;
	check_time = tmp->sim_start + tmp->time_to_die;
	while (tmp)
	{
		pthread_mutex_init(&tmp->fork, NULL);
		// pthread_mutex_init(&tmp->death, NULL);
		tmp->death = &death;
		tmp->action = &check;
		pthread_create(&tmp->philo_thread, NULL, (void *)&routine, (void *)tmp);
		pthread_detach(tmp->philo_thread);
		tmp = tmp->next;
		if (tmp == philo_lst->top)
		{
			break;
		}
	}
			while (1)
			{
				// pthread_mutex_lock(&philo_lst->top->action);
				// usleep__(philo_lst->top->time_to_die);
				if (check_death(philo_lst))
				{
					break ;
				}
				usleep(50);
				// pthread_mutex_unlock(&philo_lst->top->action);
			}
	
	// wait_for_philos(philo_lst);
	// pthread_mutex_unlock(philo_lst->top->action);
	return (0);
}
int	main(int argc, char **argv)
{
	long long sim_start;
	// struct	timeval tv;
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
		sim_start = get_current();
		if (!add_philosophers(philo_lst, argv, sim_start))
			return (1);
		init_philos(philo_lst);
		// destroy_all_forks(philo_lst->top);
		// wait_for_philos(philo_lst);
	}
	return (0);
}