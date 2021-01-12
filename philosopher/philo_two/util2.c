/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:30:25 by amoujane          #+#    #+#             */
/*   Updated: 2021/01/12 17:22:50 by amoujane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		ft_free(void)
{
	int i;

	i = 0;
	while (i < g_data.amount / 2)
	{
		sem_post(g_lock);
		i++;
	}
	sem_close(g_lock);
	sem_unlink("g_lock");
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
	sem_wait(g_lock);
	if (ft_time_test(ft_time(), g_philos[index].last_meal) > g_data.time_to_die)
	{
		g_philos[index].died = 1;
		sem_post(g_lock);
		return (1);
	}
	sem_post(g_lock);
	return (0);
}

void	ft_destr(void)
{
	int i;

	i = 0;
	while (i < g_data.amount / 2)
	{
		sem_post(g_lock);
		i++;
	}
	sem_close(g_lock);
	sem_unlink("g_lock");
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
