/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:30:25 by amoujane          #+#    #+#             */
/*   Updated: 2021/01/13 16:03:32 by amoujane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		ft_free(void)
{
	int i;

	i = 0;
	while (i < g_data.amount)
	{
		pthread_mutex_destroy(&g_philos[i].lock);
		i++;
	}
	free(g_philos);
	return (1);
}

int		start_threads(void)
{
	int			i;
	pthread_t	thread_id[g_data.amount];

	i = 0;
	g_data.start = ft_time();
	while (i < g_data.amount)
	{
		pthread_create(&thread_id[i], NULL, ft_lunch, &g_philos[i]);
		pthread_detach(thread_id[i]);
		i++;
	}
	return (0);
}

int		ft_check(int index)
{
	pthread_mutex_lock(&g_philos[index].lock);
	if (ft_time_test(ft_time(), g_philos[index].last_meal) > g_data.time_to_die)
	{
		g_philos[index].died = 1;
		pthread_mutex_unlock(&g_philos[index].lock);
		return (1);
	}
	pthread_mutex_unlock(&g_philos[index].lock);
	return (0);
}

void	ft_destr(void)
{
	int i;

	i = 0;
	while (i < g_data.amount)
	{
		pthread_mutex_destroy(&g_philos[i].lock);
		i++;
	}
	free(g_philos);
}

int		ft_print_max_time(int check, int i)
{
	if (g_times_eat_check\
	&& (g_philos[i].times_eat >= g_data.must_eat_count)\
	&& (g_philos[i].check != -1))
	{
		g_philos[i].check = -1;
		check++;
		ft_display_message("MAX_TIME\n", g_philos[i].index);
	}
	return (check);
}
