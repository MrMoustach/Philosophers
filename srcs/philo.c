/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 10:55:03 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/15 14:16:14 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

t_philo	*ft_new_philo(int id, suseconds_t added)
{
	t_philo	*ret;

	ret = (t_philo *)malloc(sizeof(t_philo));
	ret->id = id;
	ret->time_added = added;
	ret->n_slept = 0;
	ret->n_ate = 0;
	ret->n_thought = 0;
	ret->last_slept = 0;
	ret->last_ate = 0;
	ret->last_thought = 0;
	ret->status = 0;
	return (ret);
}

t_table	add_philo(t_table table, int id)
{
	struct timeval	tv;
	t_philo			*philo;

	gettimeofday(&tv, NULL);
	philo = ft_new_philo(id + 1, tv.tv_usec);
	ft_add_clist(&table.philos, ft_new_clist(philo));
	pthread_mutex_init(&table.forks[id], NULL);
	return (table);
}

void	free_philos(void)
{
	t_clist	*tmp;

	tmp = g_table.philos;
	while (tmp->next)
	{
		pthread_mutex_destroy(&g_table.forks[tmp->content->id]);
		free (tmp->content);
		tmp = tmp->next;
		if (tmp == g_table.philos)
			break ;
	}
}

void	start_simulation(void)
{
	t_clist	*tmp;
	int		i;

	i = 0;
	while (i < g_table.count)
		g_table = add_philo(g_table, i++);
	g_table.started_at = get_time();
	tmp = g_table.philos;
	while (tmp->next)
	{
		pthread_create(&(tmp->content->tid), NULL, &routine, tmp->content);
		usleep(100);
		tmp = tmp->next;
		if (tmp == g_table.philos)
			break ;
	}
}
