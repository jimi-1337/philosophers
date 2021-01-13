/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:15:33 by amoujane          #+#    #+#             */
/*   Updated: 2021/01/13 16:13:20 by amoujane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

struct timeval	ft_time(void)
{
	struct timeval ret;

	gettimeofday(&ret, NULL);
	return (ret);
}

int				ft_time_test(struct timeval ret, struct timeval philotime)
{
	int r;

	r = ((ret.tv_sec - philotime.tv_sec) * 1000) +
	((ret.tv_usec - philotime.tv_usec) / 1000);
	return (r);
}

void			ft_lunch_thread(int index)
{
	pthread_t	p;
	int			new;

	new = index;
	pthread_create(&p, NULL, ft_check_fork, &new);
	pthread_detach(p);
}

void			ft_exit_sem(void)
{
	int i;

	i = 0;
	while (i < g_data.amount / 2)
	{
		sem_post(g_lock);
		i++;
	}
	exit(1);
}

void			*ft_check_fork(void *a)
{
	int num;

	num = *(int*)a;
	while (1)
	{
		if (ft_time_test(ft_time(), g_philos[num].last_meal) >
		g_data.time_to_die)
		{
			g_philos[num].died = 1;
			ft_display_message("died\n", g_philos[num].index);
			ft_exit_sem();
			return (NULL);
		}
		usleep(10);
	}
}
