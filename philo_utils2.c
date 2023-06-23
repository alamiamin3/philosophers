/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 10:34:28 by aalami            #+#    #+#             */
/*   Updated: 2023/06/23 12:07:27 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_current(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(time_t time_stamps)
{
	long long	current;

	current = get_current();
	while (get_current() - current < time_stamps)
	{
		usleep(50);
	}
}

int	check_is_numerique(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (str[i] == '\0')
		return (0);
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			break ;
		flag = 1;
		i++;
	}
	if (flag)
	{
		while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
			i++;
		if (str[i] == '\0')
			return (1);
		return (0);
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (0);
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0 || !check_is_numerique(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

void	print_actions(t_philo *tmp, int stat)
{
	pthread_mutex_lock(tmp->action);
	if (stat == 1)
		printf("%lld philo %d take a fork\n", get_current() - tmp->sim_start,
			tmp->index);
	else if (stat == 2)
	{
		printf("%lld philo %d is eating\n", get_current() - tmp->sim_start,
			tmp->index);
		tmp->starvation = get_current() + tmp->time_to_die;
		if (tmp->number_of_meals != -1)
		{
			tmp->number_of_meals--;
			if (tmp->number_of_meals == 0)
				tmp->finished = 1;
		}
	}
	else if (stat == 3)
		printf("%lld philo %d is sleeping\n", get_current() - tmp->sim_start,
			tmp->index);
	else
		printf("%lld philo %d is thinking\n", get_current() - tmp->sim_start,
			tmp->index);
	pthread_mutex_unlock(tmp->action);
}
