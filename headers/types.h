/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 11:13:49 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/04 18:33:08 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H
# include <sys/time.h>
# include <pthread.h>

enum status {SLEEPING, THINKING, EATING};

typedef struct s_philo
{
		int				id;
		suseconds_t		time_added;
		int				n_slept;
		int				n_ate;
		int				n_thought;
		int				last_slept;
		int				last_ate;
		int				last_thought;
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
		int				iteration;
		int				time_passed;
		int				time_to_die;
		int				time_to_eat;
		int				time_to_sleep;
		int				max_n_eat;
		pthread_mutex_t	*forks;
		pthread_mutex_t print;
		int				error;
}				t_table;
#endif