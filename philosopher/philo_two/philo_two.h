/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:16:31 by amoujane          #+#    #+#             */
/*   Updated: 2021/01/12 17:51:57 by amoujane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct		s_philo
{
	int				index;
	int				fork;
	int				right;
	int				die;
	int				sleep;
	int				eat;
	int				died;
	int				times_eat;
	int				times_eat_check;
	int				max;
	int				check;
	struct timeval	last_meal;
}					t_philo;

typedef struct		s_data
{
	int				amount;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	struct timeval	start;
}					t_data;

void				ft_destr();
void				ft_work(int index);
int					ft_check_one(void);
int					ft_sleep(int index);
int					ft_time_test(struct timeval ret, struct timeval philotime);
struct timeval		ft_time();
void				ft_display_message(char *str, int index);
int					ft_strlen(char *str);
int					ft_exit(char *str);
int					ft_atoi(char *str);
void				ft_putnbr_fd(int n, int fd);
void				*ft_lunch(void *i);
void				ft_start(int c);
int					init(int ac, char **av);
int					ft_free(void);
int					start_threads(void);
int					ft_print_max_time(int check, int i);

sem_t				*g_lock;
t_philo				*g_philos;
t_data				g_data;
int					g_times_eat_check;
#endif
