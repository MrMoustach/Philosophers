/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 11:13:49 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/14 17:55:10 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H
# include <sys/time.h>
# include <pthread.h>

enum status {SLEEPING, THINKING, EATING, FORK_1, FORK_2, DEAD};

typedef struct s_philo
{
		int				id;
		suseconds_t		time_added;
		int				n_slept;
		int				n_ate;
		int				n_thought;
		size_t			last_slept;
		size_t			last_ate;
		size_t			last_thought;
		enum status		status;
		pthread_t		tid;
		pthread_mutex_t the_fork;
}               t_philo;

typedef struct s_clist 
{
	t_philo			*content;
	struct s_clist	*next;
	int				index;
}			   t_clist;

typedef struct s_table
{
		t_clist			*philos;
		int				count;
		int				time_to_die;
		int				time_to_eat;
		int				time_to_sleep;
		int				max_n_eat;
		pthread_mutex_t	*forks;
		pthread_mutex_t print;
		int				error;
		size_t			started_at;
}				t_table;
#endif