/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:30:25 by amoujane          #+#    #+#             */
/*   Updated: 2021/01/11 19:32:55 by amoujane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo_one.h"

int		ft_free(void)
{
	int i;

	i = 0;
	while (i < g_data.amount)
	{
		pthread_mutex_destroy(&g_philos[i].lock);
		i++;
	}
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
}
