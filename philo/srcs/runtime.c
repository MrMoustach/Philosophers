/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 14:10:55 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/15 14:14:04 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	express(t_philo	philo, size_t time)
{
	pthread_mutex_lock(&g_table.print);
	if (philo.status == FORK_1)
		printf("%zu %d has taken his fork\n", time, philo.id);
	if (philo.status == FORK_2)
		printf("%zu %d has taken second fork\n", time, philo.id);
	if (philo.status == SLEEPING)
		printf("%zu %d is sleeping\n", time, philo.id);
	if (philo.status == THINKING)
		printf("%zu %d is thinking\n", time, philo.id);
	if (philo.status == EATING)
		printf("%zu %d is eating\n", time, philo.id);
	pthread_mutex_unlock(&g_table.print);
}

int	destroy_table(int id, enum e_end status)
{
	pthread_mutex_lock(&g_table.print);
	if (status == E_DEAD)
		printf("%zu %d died\n", get_time(), id);
	pthread_mutex_destroy(&g_table.print);
	free_philos();
	free (g_table.forks);
	return ((int) status);
}

void	*routine(void *content)
{
	t_philo	*philo;

	philo = (t_philo *) content;
	while (1)
	{
		if (philo->id % 2 == 0 || philo->n_ate)
			philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
	}
}

t_table	init_table(int ac, char *av[])
{
	t_table	table;
	int		i;

	table.error = 0;
	table.philos = NULL;
	if (!(ac == 6 || ac == 5))
	{
		table.error = -1;
		return (table);
	}
	table.count = try_parse_int(av[1], &table.error);
	table.time_to_die = try_parse_int(av[2], &table.error);
	table.time_to_eat = try_parse_int(av[3], &table.error);
	table.time_to_sleep = try_parse_int(av[4], &table.error);
	table.max_n_eat = -1;
	if (ac == 6)
		table.max_n_eat = try_parse_int(av[5], &table.error);
	table.started_at = 0;
	if (table.error == 0)
	{
		pthread_mutex_init(&table.print, NULL);
		table.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
				* table.count);
	}
	return (table);
}

int	supervisor(void)
{
	t_clist	*tmp;
	int		i;

	while (1)
	{
		tmp = g_table.philos;
		i = 0;
		while (tmp->next)
		{
			if (tmp->content->n_ate >= g_table.max_n_eat)
				i++;
			if ((get_time() - tmp->content->last_ate >= g_table.time_to_die)
				&& tmp->content->status != EATING)
			{	
				tmp->content->status = DEAD;
				return (destroy_table(tmp->content->id, E_DEAD));
			}
			tmp = tmp->next;
			if (tmp == g_table.philos)
				break ;
		}
		if (i == g_table.count && g_table.max_n_eat > 0)
			return (destroy_table(-1, COMPLETED));
	}
}
