/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:15:33 by amoujane          #+#    #+#             */
/*   Updated: 2021/01/11 19:18:28 by amoujane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo_one.h"

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
