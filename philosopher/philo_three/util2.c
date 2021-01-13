/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:30:25 by amoujane          #+#    #+#             */
/*   Updated: 2021/01/12 19:31:47 by amoujane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
	int		i;
	int		save;
	int		status;

	i = 0;
	save = 0;
	status = 0;
	g_data.start = ft_time();
	while (i < g_data.amount)
	{
		if ((save = fork()) == 0)
			ft_start(i);
		else
			g_ids[i] = save;
		i++;
	}
	i = 0;
	while (WEXITSTATUS(status) == 0 && i < g_data.amount)
	{
		waitpid(g_ids[i], &status, 0);
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

void	ft_print_max_time(int index)
{
	if (g_times_eat_check &&
	(g_philos[index].times_eat >= g_philos[index].max))
	{
		ft_display_message("max times\n", g_philos[index].index);
		sem_post(g_lock);
		sem_unlink("g_lock");
		exit(0);
	}
}
